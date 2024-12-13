#include "StealResourceState.h"
#include "ResourceHandlingState.h"
#include "Game.h"
#include <iostream>

#define STEAL_RESOURCE_STATE 8

namespace state{

StealResourceState::~StealResourceState(){
    std::cout <<"destructor called"<< std::endl;
}

void StealResourceState::handle(){
    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);
}

int StealResourceState::getStateId(){
    return STEAL_RESOURCE_STATE;
}

}