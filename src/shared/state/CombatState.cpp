#include "CombatState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include <iostream>

void state::CombatState::handle1(){
}

void state::CombatState::handle2(){
    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);
}
