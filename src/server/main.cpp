#include "server.h"
#include "client.h"
#include <iostream>

int main() {
    // Créer une instance du serveur
    server::Server server;
    client::Client *client = new client::Client();
    server.addObserver(client);
    // Démarrer le serveur sur le port 53000
    server.start(53000);

    return 0;
}