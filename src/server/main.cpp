#include "server.h"
#include <iostream>

int main() {
    // Créer une instance du serveur
    server::Server server;

    // Démarrer le serveur sur le port 53000
    server.start(53000);

    return 0;
}