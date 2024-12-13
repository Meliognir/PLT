#include "CombatAttackingState.h"
#include "StealResourceState.h"
#include "CombatDefendingState.h"
#include "Game.h"
#include "Player.h"
#include <iostream>

state::CombatAttackingState::~CombatAttackingState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::CombatAttackingState::handle(){
    Player * attacker = game->getAttackingPlayer();
    int attackpower = attacker->getFirePower(); 
    if (attackpower>1000){
        game->setCombatWinner(attacker);
        std::cout <<"Transitioning to StealResource state..."<< std::endl;
        game->transitionTo(new StealResourceState);
    }
    else {
        game->transitionTo(new CombatDefendingState);
    }
}
