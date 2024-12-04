#include "CardChoiceState.h"
#include "CardActionState.h"
#include "Game.h"
#include <iostream>

state::CardChoiceState::~CardChoiceState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::CardChoiceState::handle(){
    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
}
