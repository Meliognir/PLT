#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
//end of test SFML


#include "../shared/state.h" //to use vscode tasks file instead of makefile
#include "../shared/engine.h"
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
    return 0;
}

int main(int argc,char* argv[])
{
    int ret;
    ret = clientcode(); // test handle 1 and 2
    return ret;
}

