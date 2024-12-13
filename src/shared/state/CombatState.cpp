#include "CombatState.h"
#include "StealResourceState.h"
#include "CardActionState.h"
#include "Game.h"
#include "Player.h"

#include <iostream>

state::CombatState::~CombatState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::CombatState::handle(){
    Player * attacker = game->getAttackingPlayer();
    Player * defender = game->getDefendingPlayer();
    int attackpower = attacker->getFirePower(); 
    int defensepower = attacker->getFirePower(); 
    if (attackpower==defensepower){
        std::cout <<" égalité : Transitioning to CardAction state..."<< std::endl;
        game->transitionTo(new CardActionState);
    }
    else if (attackpower>defensepower){
        game->setCombatWinner(attacker);
    }
    else {
        game->setCombatWinner(defender);
    }
    std::cout <<"Transitioning to StealResource state..."<< std::endl;
    game->transitionTo(new StealResourceState);
}
