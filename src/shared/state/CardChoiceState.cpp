#include "CardChoiceState.h"
#include "CardActionState.h"
#include "Game.h"
#include <iostream>

void state::CardChoiceState::handle1(){
}

void state::CardChoiceState::handle2(){
    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
}
