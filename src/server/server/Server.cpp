
#include "Server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm> // Pour std::max

bool starts_with(const std::string& str, const std::string& prefix) { return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0; }
namespace server {

Server::Server() : nextClientId(0), maxFd(0), listenerFd(-1) {
    FD_ZERO(&masterSet); // Initialiser l'ensemble des sockets
}

Server::~Server() {
    if (listenerFd != -1) {
        close(listenerFd);
    }

    for (auto& [id, fd] : clients) {
        close(fd);
    }
}

void Server::start(int port) {
    listenerFd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenerFd < 0) {
        perror("Erreur : Impossible de créer le socket d'écoute.");
        return;
    }

    sockaddr_in serverAddr{};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenerFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Erreur : Impossible de lier le socket au port.");
        close(listenerFd);
        return;
    }

    if (listen(listenerFd, 5) < 0) {
        perror("Erreur : Impossible de mettre le socket en écoute.");
        close(listenerFd);
        return;
    }

    std::cout << "Serveur en écoute sur le port " << port << "." << std::endl;

    FD_SET(listenerFd, &masterSet);
    maxFd = listenerFd;

    handleConnections();
}

void Server::handleConnections() {
    while (true) {
        fd_set readSet = masterSet;

        if (select(maxFd + 1, &readSet, nullptr, nullptr, nullptr) < 0) {
            perror("Erreur lors de l'appel à select.");
            break;
        }

        for (int fd = 0; fd <= maxFd; fd++) {
            if (FD_ISSET(fd, &readSet)) {
                if (fd == listenerFd) { // Nouveau client
                    sockaddr_in clientAddr{};
                    socklen_t clientLen = sizeof(clientAddr);
                    int clientFd = accept(listenerFd, (struct sockaddr*)&clientAddr, &clientLen);

                    if (clientFd < 0) {
                        perror("Erreur lors de l'acceptation d'une connexion.");
                        continue;
                    }

                    FD_SET(clientFd, &masterSet);
                    maxFd = std::max(maxFd, clientFd);

                    int clientId = nextClientId++;
                    clients[clientId] = clientFd;
                    std::cout << "Nouveau client connecté : ID " << clientId << std::endl;


                } else {
                    handleClientMessage(fd);
                }
            }
        }
    }
}

void Server::handleClientMessage(int clientFd) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
    if (bytesRead <= 0) {
        std::cerr << "Client déconnecté (fd: " << clientFd << ")." << std::endl;
        close(clientFd);
        FD_CLR(clientFd, &masterSet);
        clients.erase(clientFd);
        return;
    }

    std::string message(buffer, bytesRead);
    std::cout << "Message reçu du client : " << message << std::endl;

    // Traiter les réponses reçues
    if (starts_with(message,"chooseNbOfPlayers")) {
        int Nb = std::stoi(message.substr(18));
        std::cout << "Nombre de joueurs choisis : " << Nb << std::endl;
        notifyObservers("chooseNbOfPlayers", std::to_string(Nb));
        // Demander une autre information
        requestInputFromClient(clientFd, "chooseNbOfPlayers");
    }
    else if (starts_with(message,"gameMode")) {
        int mode = std::stoi(message.substr(9));
        std::cout << "Mode de jeu choisi : " << mode << std::endl;
        notifyObservers("gameModeSelected", std::to_string(mode));
        // Demander une autre information
        requestInputFromClient(clientFd, "getPlayerName");
    } else if (starts_with(message,"playerName")) {
        std::string playerName = message.substr(11);
        std::cout << "Nom du joueur reçu : " << playerName << std::endl;
        notifyObservers("playerNameReceived", playerName);
        // Continuer avec d'autres étapes du jeu
    } else {
        std::cout << "Commande inconnue reçue : " << message << std::endl;
    }
}

void Server::sendCommandToClient(int clientFd, const std::string& command) {
    if (send(clientFd, command.c_str(), command.size(), 0) < 0) {
        std::cerr << "Erreur lors de l'envoi de la commande au client (fd: " << clientFd << ")." << std::endl;
    } else {
        std::cout << "Commande envoyée au client (fd: " << clientFd << ") : " << command << std::endl;
    }
}

void Server::requestInputFromClient (int clientFd, const std::string& inputType) {
    sendCommandToClient(clientFd, inputType);
}

} // namespace server
