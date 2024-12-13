#include "CombatDefendingState.h"
#include "CardActionState.h"
#include "StealResourceState.h"
#include "Game.h"
#include "Player.h"
#include "iostream"
state::CombatDefendingState::~CombatDefendingState(){
    std::cout <<"destructor called"<< std::endl;
}

void state::CombatDefendingState::handle(){
    Player * attacker = game->getAttackingPlayer();
    int attackpower = attacker->getFirePower(); 
    Player * defender = game->getDefendingPlayer();
    int defensepower = defender->getFirePower(); 
    if (attackpower == defensepower){
        std::cout <<"Egalite : Transitioning to CardAction state..."<< std::endl;
        game->transitionTo(new CardActionState);
    }
    else if (attackpower > defensepower){
        game->setCombatWinner(attacker);
    }
    else {
        game->setCombatWinner(defender);
    }
    std::cout <<"Transitioning to StealResource state..."<< std::endl;
    game->transitionTo(new StealResourceState);
}
