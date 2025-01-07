#include "CombatDefendingState.h"
#include "CardActionState.h"
#include "StealResourceState.h"
#include "Game.h"
#include "Player.h"
#include "Observable.h"
#include "iostream"

#define COMBAT_DEFENDING_STATE 7


namespace state{

void state::CombatDefendingState::handle(){

    Player *activePlayer = game->getActivePlayer();
    activePlayer->setPrevDuel(true); // à déplacer après la fin du combat dans stealresourcestate

    Player * attacker = game->getAttackingPlayer();
    int attackpower = attacker->getFirePower(); 
    Player * defender = game->getDefendingPlayer();
    int defensepower = defender->getFirePower(); 

    std::cout << "Attacking Firepower: " << attackpower << ", Defending Firepower: " << defensepower << "\r\n" << std::endl;
    
    if (attackpower == defensepower){

        std::cout <<"Egalite : Transitioning to CardAction state..."<< std::endl;
        game->transitionTo(new CardActionState);
        notifyObservers();
    }
    else if (attackpower > defensepower){
        game->setCombatWinner(attacker);
    }
    else {
        game->setCombatWinner(defender);
    }

    std::cout <<"Transitioning to StealResource state..."<< std::endl;
    game->transitionTo(new StealResourceState);
    notifyObservers();
}

int CombatDefendingState::getStateId(){
    return COMBAT_DEFENDING_STATE;
}

state::CombatDefendingState::~CombatDefendingState(){
    std::cout <<"destructor called"<< std::endl;
}

}