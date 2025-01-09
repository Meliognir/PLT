#include "Server.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

namespace server {

    Server::Server() : listenerFd(-1) {}

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
            std::cerr << "Erreur : Impossible de créer le socket d'écoute." << std::endl;
            return;
        }

        sockaddr_in serverAddr{};
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(listenerFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Erreur : Impossible de lier le socket au port." << std::endl;
            close(listenerFd);
            return;
        }

        if (listen(listenerFd, 5) < 0) {
            std::cerr << "Erreur : Impossible de mettre le socket en écoute." << std::endl;
            close(listenerFd);
            return;
        }

        std::cout << "Serveur en écoute sur le port " << port << "." << std::endl;

        int clientId = 0;
        while (true) {
            sockaddr_in clientAddr{};
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientFd = accept(listenerFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
            if (clientFd < 0) {
                std::cerr << "Erreur lors de l'acceptation d'une connexion." << std::endl;
                continue;
            }

            clients[clientId] = clientFd;
            std::cout << "Client " << clientId << " connecté." << std::endl;
            handleClientMessage(clientId);
            clientId++;
        }
    }

    void Server::handleClientMessage(int clientId) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = recv(clients[clientId], buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            std::cerr << "Client " << clientId << " déconnecté." << std::endl;
            close(clients[clientId]);
            clients.erase(clientId);
            return;
        }

        std::string command(buffer, bytesRead);
        std::cout << "Commande reçue du client " << clientId << ": " << command << std::endl;

        // Exemple : Diffusion de l'état du jeu
        broadcastGameState("Etat du jeu mis à jour");
    }

    void Server::broadcastGameState(const std::string& gameState) {
        for (auto& [id, fd] : clients) {
            if (send(fd, gameState.c_str(), gameState.size(), 0) < 0) {
                std::cerr << "Erreur lors de l'envoi à client " << id << "." << std::endl;
            }
        }
    }
}