#include "StealResourceState.h"
#include "ResourceHandlingState.h"
#include "Observable.h"
#include "Game.h"
#include <iostream>

#define STEAL_RESOURCE_STATE 8

namespace state{

StealResourceState::~StealResourceState(){
    std::cout <<"destructor called"<< std::endl;
}

void StealResourceState::handle(){

    Player * winner = game->getCombatWinner();
    Player * loser = game->getCombatLoser();
    std::cout << "Player: " << winner->getName() << " wins and Player: " << loser->getName() << " loses." << std::endl;

    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);
    notifyObservers();
}

int StealResourceState::getStateId(){
    return STEAL_RESOURCE_STATE;
}

}