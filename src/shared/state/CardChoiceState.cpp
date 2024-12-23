#include "CardChoiceState.h"
#include "CardActionState.h"
#include "Game.h"
#include "Observable.h"
#include <iostream>


#define CARD_CHOICE_STATE 2


namespace state{

CardChoiceState::~CardChoiceState(){
    std::cout <<"destructor called"<< std::endl;
}


void CardChoiceState::handle(){
    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
    notifyObservers();
}

int CardChoiceState::getStateId(){
    return CARD_CHOICE_STATE;
}


}