#include "CombatAttackingState.h"
#include "StealResourceState.h"
#include "CombatDefendingState.h"
#include "Game.h"
#include "Player.h"
#include "Observable.h"
#include <iostream>

#define COMBAT_ATTACKING_STATE 6

namespace state{


void CombatAttackingState::handle(){
    Player * attacker = game->getAttackingPlayer();
    int attackpower = attacker->getFirePower(); 
    if (attackpower>1000){
        game->setCombatWinner(attacker);
        std::cout <<"Transitioning to StealResource state..."<< std::endl;
        game->transitionTo(new StealResourceState);
        notifyObservers();
    }
    else {
        game->transitionTo(new CombatDefendingState);
        notifyObservers();
    }
}


int CombatAttackingState::getStateId(){
    return COMBAT_ATTACKING_STATE;
}

CombatAttackingState::~CombatAttackingState(){
    std::cout <<"destructor called"<< std::endl;
}

}
