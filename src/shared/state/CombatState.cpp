#include "CombatState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include <iostream>

state::CombatState::~CombatState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::CombatState::handle(){
    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);
}
