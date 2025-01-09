#include "server/NetworkClient.h"
#include <iostream>

int main() {
    // Créer une instance du client réseau
    server::NetworkClient client;

    // Connecter au serveur
    client.connectToServer("127.0.0.1", 53000);

    // Vérifier si la connexion a réussi
    if (client.recieveGameState().empty()) {
        std::cerr << "Erreur : Impossible de se connecter au serveur ou état non reçu." << std::endl;
        return -1;
    }

    // Boucle pour interagir avec le serveur
    while (true) {
        std::string command;
        std::cout << "Entrez une commande (move/end_turn/quit) : ";
        std::cin >> command;

        if (command == "move") {
            int distance, direction;
            std::cout << "Entrez la distance et la direction : ";
            std::cin >> distance >> direction;

            // Envoyer la commande au serveur
            client.sendCommand(command, {distance, direction});
        } else if (command == "end_turn") {
            // Envoyer une commande de fin de tour
            client.sendCommand(command, {});
        } else if (command == "quit") {
            std::cout << "Déconnexion..." << std::endl;
            break;
        } else {
            std::cerr << "Commande inconnue !" << std::endl;
        }

        // Recevoir l'état du jeu mis à jour
        std::string gameState = client.recieveGameState();
        std::cout << "État du jeu : " << gameState << std::endl;
    }

    return 0;
}