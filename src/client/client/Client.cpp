#include "client.h"
#include "state.h"

#include <iostream>

namespace client{

Client::Client()
{

//-----------------------------
// instantiates a new Game context and runs concrete states "GameConfig" then "Playing" functions
//-----------------------------

    gameState = new state::GameConfigState();
    gameEngine = new engine::GameEngine(gameState);

    //Game *mygame = new Game(new GameConfigState); //transition to GameConfig


}


int Client::launch(){
    gameEngine->initializeGame(10);
    
    gameEngine->steps();
    
    return 0;

    //if (*gameState == gameConfigState);
}


}