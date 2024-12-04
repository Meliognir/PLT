#include "OpponentChoiceState.h"
#include "Game.h"
#include "CombatState.h"
#include <iostream>

state::OpponentChoiceState::~OpponentChoiceState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::OpponentChoiceState::handle(){
    std::cout <<"Transitioning to Combat state..."<< std::endl;
    game->transitionTo(new CombatState);
}
