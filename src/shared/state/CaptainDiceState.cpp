#include "CaptainDiceState.h"
#include "CardChoiceState.cpp"
#include "Game.h"
#include <iostream>
namespace state{
void CaptainDiceState::handle1(){

}

void CaptainDiceState::handle2(){
    std::cout <<"Transitioning to CardChoice state..."<< std::endl;
    game->transitionTo(new CardChoiceState);
}

}
