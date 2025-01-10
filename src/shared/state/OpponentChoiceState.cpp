#include "OpponentChoiceState.h"
#include "ResourceHandlingState.h"
#include "Game.h"
#include "CombatAttackingState.h"
#include "Observable.h"
#include <iostream>

#define OPPONENT_CHOICE_STATE 5

namespace state{
void OpponentChoiceState::handle(){
   
    //test
    // std::cout <<"Transitioning to ResourceHandlingState state..."<< std::endl;
    // game->transitionTo(new ResourceHandlingState);
    // notifyObservers();

    //à décommenter
    std::cout <<"Transitioning to CombatAttacking state..."<< std::endl;
    game->transitionTo(new CombatAttackingState);
    notifyObservers();
}

OpponentChoiceState::~OpponentChoiceState(){
    std::cout <<"destructor called"<< std::endl;
}

int OpponentChoiceState::getStateId(){
    return OPPONENT_CHOICE_STATE;
}


}