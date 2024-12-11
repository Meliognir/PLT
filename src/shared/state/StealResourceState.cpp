#include "StealResourceState.h"
#include "ResourceHandlingState.h"
#include "Game.h"
#include <iostream>

state::StealResourceState::~StealResourceState(){
    std::cout <<"destructor called"<< std::endl;
}

void state::StealResourceState::handle(){
    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);
}
