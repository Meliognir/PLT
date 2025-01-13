#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include "GameOverState.h"
#include "CaptainDiceState.h"
#include "Observable.h"
#include <iostream>
#include "Map.h"

#define RESOURCE_HANDLING_STATE 4

namespace state {

void ResourceHandlingState::handle(){
    Player *activePlayer = game->getActivePlayer();
    if (activePlayer->getMustFight()){
        std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
        game->transitionTo(new OpponentChoiceState);
        notifyObservers();
    }
    else{

        unsigned actionCounter = (unsigned) game->actionCounter;

        // check the end condition:
        if (!game->getGameOver()){
            for(Player * pl : game->getPlayerList()){
                if(pl->getPosition() == game->getMap()->getSize()){
                    game->setGameOver(true);
                }
            }
            if (game->getGameOver() && actionCounter % 2){
                actionCounter++;
            }
        }

        // transition to next state accordingly

        //fin des actions de tous les joueurs
        if(actionCounter >= game->getPlayerList().size()*2) {
            //end of turn
            if(game->getGameOver()){
                std::cout <<"Transitioning to GameOver state..."<< std::endl;
                game->transitionTo(new GameOverState);
            }
            else{
                std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
                game->transitionTo(new CaptainDiceState);
            }
            notifyObservers();
        }
        else{


            std::cout <<"Transitioning to CardActionState state..."<< std::endl;
            game->transitionTo(new CardActionState);
            notifyObservers();  
        }
    }
    
}

ResourceHandlingState::~ResourceHandlingState(){
    std::cout <<"destructor called"<< std::endl;
}

int ResourceHandlingState::getStateId(){
    return RESOURCE_HANDLING_STATE;
}

}