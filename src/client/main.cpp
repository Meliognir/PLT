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

void clientThreadFunction(client::Client* client) {
    client->launch(); // Exécute la logique du client sur un thread séparé
}

int main(int argc,char* argv[])
{
    render::Renderer* renderer = new render::Renderer();
    client::Client *client = new client::Client();
    Game * game = client->gameInstance;
    // Démarrer le thread pour le client
    std::thread clientThread(clientThreadFunction, client);
    // Attendre que la carte soit prête
    while (client->running && !game->isMapInitialized()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause pour éviter un busy-wait trop intense
    }

    sf::RenderWindow *window;
    if (client->running) {window = new sf::RenderWindow(sf::VideoMode(2100, 1400), "Parcours circulaire");}
    // Boucle principale pour le rendu
    while (window->isOpen() && client->running) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        // Appel à renderMap ici
        {
            if (game->map) {
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, Game::dayDie, Game::nightDie);
            }
        }
        {
        renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
        }
        window->display();
    }


    //When the window is closed, we need to stop the client thread too :   
    //Use pthread instead of thread and request_stop() instead of join()   ?
    //clientThread.request_stop();  ?
    // while (!client->closing) {display();}
    clientThread.join();
    delete renderer;
    delete client;
    delete game;
    return 0;
}
