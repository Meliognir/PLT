#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include <iostream>

void state::ResourceHandlingState::handle1(){
}

void state::ResourceHandlingState::handle2(){
    //si on peut payer et joueurs présents sur case
    std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
    game->transitionTo(new OpponentChoiceState);


    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
}

