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

    //set prevduel to true so that you don't fight 2 times on the same tile
    Player *activePlayer = game->getActivePlayer();
    activePlayer->setPrevDuel(true);

    Player * attacker = game->getAttackingPlayer();
    int attackpower = attacker->getFirePower();
    Player * defender = game->getDefendingPlayer();
    int defensepower = defender->getFirePower();

    if (attackpower>1000){
        std::cout << "Player: " << attacker->getName() << " wins because attackpower > 1000" << std::endl;

        game->setCombatWinner(attacker);
        game->setCombatLoser(defender);

        std::cout <<"Transitioning to StealResource state..."<< std::endl;
        game->transitionTo(new StealResourceState);
        notifyObservers();
    }
    else {
        std::cout <<"Transitioning to CombatDefending state..."<< std::endl;
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
