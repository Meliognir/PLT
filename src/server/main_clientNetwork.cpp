#include "server/NetworkClient.h"
#include <iostream>

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    // Création du socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(53000);
    inet_pton(AF_INET, "10.0.2.15", &serverAddr.sin_addr);

    // Connexion au serveur
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        close(sock);
        return 1;
    }

    std::cout << "Connecté au serveur. Tapez 'exit' pour quitter." << std::endl;

    char buffer[1024];
    while (true) {
        // Saisie de l'utilisateur
        std::cout << "Votre commande : ";
        std::string input;
        std::getline(std::cin, input);

        // Envoi de la commande
        if (send(sock, input.c_str(), input.size(), 0) < 0) {
            perror("Erreur lors de l'envoi de la commande");
            break;
        }

        if (input == "exit") {
            std::cout << "Déconnexion." << std::endl;
            break;
        }

        // Réception de la réponse
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead > 0) {
            std::cout << "Réponse du serveur : " << buffer << std::endl;
        } else if (bytesRead == 0) {
            std::cout << "Le serveur a fermé la connexion." << std::endl;
            break;
        } else {
            perror("Erreur lors de la réception");
            break;
        }
    }

    close(sock);
    return 0;
}