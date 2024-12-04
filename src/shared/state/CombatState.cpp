#include "CombatState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include <iostream>

state::CombatState::~CombatState(){
    std::cout <<"destructor called"<< std::endl;
}

void state::CombatState::handle1(){
}

void state::CombatState::handle2(){
    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);
}
