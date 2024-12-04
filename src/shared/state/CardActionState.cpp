#include "CardActionState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include "CaptainDiceState.cpp"
#include <iostream>

void state::CardActionState::handle1(){
}

void state::CardActionState::handle2(){
    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);

    //en fin de tour, on passe au prochain tour
    std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
    game->transitionTo(new CaptainDiceState);
}
