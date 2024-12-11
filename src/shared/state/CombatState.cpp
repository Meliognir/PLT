#include "CombatState.h"
#include "Game.h"
#include "StealResourceState.h"
#include <iostream>

state::CombatState::~CombatState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::CombatState::handle(){

    std::cout <<"Transitioning to StealResource state..."<< std::endl;
    game->transitionTo(new StealResourceState);
}
