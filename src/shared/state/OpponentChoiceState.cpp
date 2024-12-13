#include "OpponentChoiceState.h"
#include "Game.h"
#include "CombatAttackingState.h"
#include <iostream>

state::OpponentChoiceState::~OpponentChoiceState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::OpponentChoiceState::handle(){
    std::cout <<"Transitioning to CombatAttacking state..."<< std::endl;
    game->transitionTo(new CombatAttackingState);
}
