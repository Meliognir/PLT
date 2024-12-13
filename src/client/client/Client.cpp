#include "client.h"
#include "state.h"

#include <iostream>

#define GAME_CONFIG_STATE 0
#define CAPTAIN_DICE_STATE 1
#define CARD_CHOICE_STATE 2
#define CARD_ACTION_STATE 3
#define RESOURCE_HANDLING_STATE 4
#define OPPONENT_CHOICE_STATE 5
#define COMBAT_ATTACKING_STATE 6
#define COMBAT_DEFENDING_STATE 7
#define STEAL_RESOURCE_STATE 8
#define GAME_OVER_STATE 9

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

/*
    // case where gameState is GAME_CONFIG_STATE:
    std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
        //do command truc
        gameState->handle();


    int endloop = 0;
    std::string waitConfirm;
    std::cout << "Client now entering the game loop\r\n" << std::endl;

    while (!endloop){

        switch (gameState->getStateId()){

            case GAME_CONFIG_STATE:
                std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case CAPTAIN_DICE_STATE:
                std::cout << "Client now entering CAPTAIN_DICE_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case CARD_CHOICE_STATE:
                std::cout << "Client now entering CARD_CHOICE_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case CARD_ACTION_STATE:
                std::cout << "Client now entering CARD_ACTION_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case RESOURCE_HANDLING_STATE:
                std::cout << "Client now entering RESOURCE_HANDLING_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case OPPONENT_CHOICE_STATE:
                std::cout << "Client now entering OPPONENT_CHOICE_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case COMBAT_ATTACKING_STATE:
                std::cout << "Client now entering COMBAT_ATTACKING_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case COMBAT_DEFENDING_STATE:
                std::cout << "Client now entering COMBAT_DEFENDING_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
            break;


            case GAME_OVER_STATE:
                std::cout << "Client now entering GAME_OVER_STATE\r\n" << std::endl;
                //do command truc
                gameState->handle();
                endloop = 1;
            break;

        }

        std::cin >> waitConfirm;
        if (waitConfirm[0] == 'n'){
            endloop = 1;
        }

    }    */
    return 0;
}


}