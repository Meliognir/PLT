#include "CaptainDiceState.h"
#include "CardChoiceState.h"
#include "Game.h"
#include <iostream>

#define CAPTAIN_DICE_STATE 1


namespace state{


void CaptainDiceState::handle(){
    std::cout <<"Transitioning to CardChoice state..."<< std::endl;
    game->transitionTo(new CardChoiceState);
    notifyObservers();
}

int CaptainDiceState::getStateId(){
    return CAPTAIN_DICE_STATE;
}


CaptainDiceState::~CaptainDiceState(){
    std::cout <<"destructor called"<< std::endl;
}

}
