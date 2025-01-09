#include "NetworkClient.h"
#include <iostream>
#include <cstring>      // Pour memset
#include <sys/socket.h> // Pour socket, connect, send, recv
#include <netinet/in.h> // Pour sockaddr_in
#include <arpa/inet.h>  // Pour inet_addr
#include <unistd.h>     // Pour close

namespace server {

    NetworkClient::NetworkClient() : socketFd(-1) {}

    NetworkClient::~NetworkClient() {
        if (socketFd != -1) {
            close(socketFd);
        }
    }

    void NetworkClient::connectToServer(const std::string& ip, int port) {
        socketFd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketFd < 0) {
            std::cerr << "Erreur : Impossible de créer le socket." << std::endl;
            return;
        }

        sockaddr_in serverAddr{};
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());

        if (connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            std::cerr << "Erreur : Impossible de se connecter au serveur." << std::endl;
            close(socketFd);
            socketFd = -1;
            return;
        }

        std::cout << "Connexion réussie au serveur " << ip << ":" << port << "." << std::endl;
    }

    std::string NetworkClient::recieveGameState() {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = recv(socketFd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead < 0) {
            std::cerr << "Erreur lors de la réception de l'état du jeu." << std::endl;
            return "";
        }

        return std::string(buffer, bytesRead);
    }

    void server::NetworkClient::sendCommand(const std::string& command, const std::vector<int>& params) {
        std::string data = command;
        for (int param : params) {
            data += " " + std::to_string(param);
        }

        if (send(socketFd, data.c_str(), data.size(), 0) < 0) {
            std::cerr << "Erreur lors de l'envoi de la commande." << std::endl;
        }
    }
}






