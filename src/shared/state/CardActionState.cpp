#include "CardActionState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include "CaptainDiceState.h"
#include <iostream>
#include <SFML/System/Time.hpp>

#define CARD_ACTION_STATE 3

int gameTurn = 0;

namespace state {
void CardActionState::handle(){

    unsigned actionCounter = (unsigned) game->actionCounter;

    //fin des actions de tous les joueurs
    if(actionCounter > game->getPlayerList().size()*2) {
        //end of turn
        std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
        game->transitionTo(new CaptainDiceState);
        notifyObservers();
    }
    else{
        std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
        game->transitionTo(new ResourceHandlingState);
        notifyObservers();
    }   
}

int CardActionState::getStateId(){
    return CARD_ACTION_STATE;
}

CardActionState::~CardActionState(){
    std::cout <<"destructor called"<< std::endl;
}

}