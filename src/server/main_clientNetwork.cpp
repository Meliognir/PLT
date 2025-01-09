
#include <SFML/Network.hpp>
#include <iostream>

int main() {
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
    if (status != sf::Socket::Done) {
        std::cerr << "Erreur : Impossible de se connecter au serveur.\n";
        return -1;
    }
    std::cout << "Connecté au serveur.\n";

    // Boucle pour envoyer des messages
    while (true) {
        std::string message;
        std::cout << "Entrez un message : ";
        std::getline(std::cin, message);

        sf::Packet packet;
        packet << message;  // Encode le message pour l'envoi
        if (socket.send(packet) != sf::Socket::Done) {
            std::cerr << "Erreur lors de l'envoi du message.\n";
        } else {
            std::cout << "Message envoyé avec succès.\n";
        }
    }
    return 0;
}
