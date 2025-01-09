
#include <SFML/Network.hpp>
#include <iostream>
#include <map>
#include <string>

// Gestion des clients connectés
std::map<int, sf::TcpSocket*> clients;

// Fonction pour diffuser un message à tous les clients
void broadcastMessage(const std::string& message) {
    for (auto& [id, socket] : clients) {
        sf::Packet packet;
        packet << message;  // Encode le message
        if (socket->send(packet) != sf::Socket::Done) {
            std::cerr << "Erreur lors de l'envoi au client " << id << std::endl;
        }
    }
}

int main() {
    // Créer un listener pour accepter les connexions
    sf::TcpListener listener;
    if (listener.listen(53000) != sf::Socket::Done) {
        std::cerr << "Erreur: Impossible d'écouter sur le port 53000." << std::endl;
        return -1;
    }

    std::cout << "Serveur en écoute sur le port 53000..." << std::endl;

    // Attendre deux connexions
    for (int i = 0; i < 2; ++i) {
        sf::TcpSocket* client = new sf::TcpSocket();
        if (listener.accept(*client) != sf::Socket::Done) {
            std::cerr << "Erreur: Impossible d'accepter une connexion." << std::endl;
            delete client;
            continue;
        }
        clients[i] = client;
        std::cout << "Client " << i << " connecté." << std::endl;
    }

    // Boucle principale
    bool running = true;
    // Boucle principale pour gérer les messages des clients
    while (running) { // 'running' peut être un booléen que vous définissez pour contrôler le serveur.
        for (auto& [id, socket] : clients) {
            sf::Packet packet;
            if (socket->receive(packet) == sf::Socket::Done) {
                std::string message;
                packet >> message;  // Décode le message reçu
                std::cout << "Reçu du client " << id << ": " << message << std::endl;

                // Diffuser le message reçu à tous les clients connectés
                std::string response = "Serveur : " + message;
                broadcastMessage(response);
            } else {
                // Gérer les erreurs ou les déconnexions
                std::cerr << "Erreur de réception du client " << id << std::endl;
            }
        }
    }



    // Nettoyer les sockets
    for (auto& [id, socket] : clients) {
        delete socket;
    }

    return 0;
}
