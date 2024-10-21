#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
//end of test SFML


#include "../shared/state.h" //to use vscode tasks file instead of makefile
//#include <state.h>


using namespace std;
using namespace state;

void displayState(Game* game);

int main(int argc,char* argv[])
{
    cout << "It works !\n" << endl;

    Player *player0 = new Player(0, "player0");

    player0->setPosition(20);
    cout << "A new player was created\n" << endl;

    cout << "player is at position :" << player0->getPosition() << endl;    

    return 0;
}

void displayState(Game *game)
{
    // Ecran principal avec la map et la position des joueurs
    int mapSize = game->map->getSize();
    printf("Affichage de la map :\n");
    for (int i = 0; i < mapSize; i++){
        printf("Affichage de la tuile i\n");
    }

    // Ecran dédié aux états actuels des joueurs et les ressources dans leur cale
    int numberOfPlayers = game->getPlayerList().size();
    for (int i = 0; i < numberOfPlayers; i++){
        printf("Affichage des informations du i-ème joueur\n");
    }
}
