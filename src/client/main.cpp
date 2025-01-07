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
    sf::RenderWindow* window;
    client::Client *client = new client::Client();
    Observable::addObserver(client);
    Game * game = client->gameInstance;
    render::Renderer* renderer = new render::Renderer();
    render::HUD* hud = new render::HUD();
    render::StateLayer * stateLayer = new render::StateLayer(renderer, hud, game, window);
    Observable::addObserver(stateLayer);
    // Démarrer le thread pour le client
    std::thread clientThread(clientThreadFunction, client);
    // Attendre que la carte soit prête

    if (client->running) {
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width ; 
    unsigned int windowHeight = desktopMode.height ;
    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Parcours circulaire");
    }
    
    if (window) {
        stateLayer->setWindow(window);
        stateLayer->runRenderLoop(client); // Exécution de la boucle de rendu
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
