
#include "Server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <algorithm> // Pour std::max

namespace server {

Server::Server() : listenerFd(-1), nextClientId(0), maxFd(0) {
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

                    // Lancer le client automatiquement
                    launchCommand();
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

        for (auto it = clients.begin(); it != clients.end(); ++it) {
            if (it->second == clientFd) {
                clients.erase(it);
                break;
            }
        }
        return;
    }

    std::string message(buffer, bytesRead);
    std::cout << "Message reçu : " << message << " (fd: " << clientFd << ")" << std::endl;

    broadcastGameState("Etat du jeu mis à jour");
}

void Server::broadcastGameState(const std::string& gameState) {
    for (const auto& [id, fd] : clients) {
        if (send(fd, gameState.c_str(), gameState.size(), 0) < 0) {
            std::cerr << "Erreur lors de l'envoi à client (fd: " << fd << ")." << std::endl;
        }
    }
}

void Server::launchCommand () {
    std::cout << "Lancement du client ./../bin/client..." << std::endl;
    int result = std::system("./../bin/client &"); // Le '&' exécute le client en arrière-plan
    if (result != 0) {
        std::cerr << "Erreur lors du lancement du client." << std::endl;
    }
}

} // namespace server
