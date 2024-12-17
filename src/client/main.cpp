#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
//end of test SFML
#include <thread>

#include "../shared/state.h" //to use vscode tasks file instead of makefile
#include "../shared/engine.h"
#include "client.h"
#include "render.h"
//#include <state.h>


using namespace std;
using namespace state;
using namespace engine; 

void clientThreadFunction(client::Client* client, Game* game) {
    client->launch(); // Exécute la logique du client sur un thread séparé
}

int main(int argc,char* argv[])
{
    int displayCounter = 0; // Compteur pour limiter l'affichage
    auto lastDisplay = std::chrono::steady_clock::now();
    render::Renderer* renderer = new render::Renderer();
    client::Client *client = new client::Client();
    std::cout << "Test 2" << std::endl;
    Game * game = client->gameEngine->game;
    // Démarrer le thread pour le client
    std::thread clientThread(clientThreadFunction, client, game);
std::cout << "Test 1" << std::endl;
    // Attendre que la carte soit prête
    while (!game->isMapInitialized()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Pause pour éviter un busy-wait trop intense
    }
    std::cout << "Thread principal" << std::endl;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Parcours circulaire");
    // Boucle principale pour le rendu
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Appel à renderMap ici
        {
            if (game->map) {
                renderer->renderMap(window, *game->map);
            }
        }
        window.display();
    }

    clientThread.join();
    delete renderer;
    delete client;
    delete game;
    return 0;
}
