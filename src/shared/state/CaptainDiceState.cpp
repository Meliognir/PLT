#include "CaptainDiceState.h"
#include "CardChoiceState.h"
#include "Game.h"
#include <iostream>
namespace state{

CaptainDiceState::~CaptainDiceState(){
    std::cout <<"destructor called"<< std::endl;
}

void CaptainDiceState::handle1(){

}

void CaptainDiceState::handle2(){
    std::cout <<"Transitioning to CardChoice state..."<< std::endl;
    game->transitionTo(new CardChoiceState);
}

}
