#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
//end of test SFML


#include "../shared/state.h" //to use vscode tasks file instead of makefile
#include "../shared/engine.h"
#include "client.h"
#include "render.h"
//#include <state.h>


using namespace std;
using namespace state;
using namespace engine; 

int clientcode(){
//-----------------------------
// instantiates a new Game context and runs concrete states "GameConfig" then "Playing" functions
//-----------------------------
    GameEngine *gameEngine = new GameEngine(new GameConfigState);
    //Game *mygame = new Game(new GameConfigState); //transition to GameConfig

    gameEngine->initializeGame(10);
    gameEngine->steps();
    return 0;
}

int main(int argc,char* argv[])
{
    /*sf::RenderWindow window(sf::VideoMode(800, 600), "Parcours circulaire");

    // Initialisation de la carte
    int mapSize = 12; // Exemple : 12 tuiles pour former un cercle
    Map gameMap(mapSize);

    // Ajout des tuiles dans la carte avec des propriétés variées
    for (int i = 0; i < mapSize; ++i) {
        std::string resourceType;
        if (i % 3 == 0) resourceType = "food";
        else if (i % 3 == 1) resourceType = "gold";
        else resourceType = "";

        bool hasTreasure = (i == 5); // Exemple : le trésor est sur la 6ème tuile
        gameMap.listOfTiles.push_back(new Tile((i + 1) * 10, resourceType, 0));
        gameMap.listOfTiles.back()->treasureAvailable = hasTreasure;
    }

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Efface l'écran
        window.clear();

        // Rendu du parcours circulaire
        render::Renderer *renderer = new render::Renderer();
        renderer->renderMap(window, gameMap);

        // Affiche le rendu
        window.display();
    }

    // Libération de la mémoire allouée pour les tuiles
    for (Tile* tile : gameMap.listOfTiles) {
        delete tile;
    }*/
    int ret;
    client::Client *client = new client::Client();
    ret = client->launch();

    return ret;
}

