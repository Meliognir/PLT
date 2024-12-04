#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include <iostream>

state::ResourceHandlingState::~ResourceHandlingState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::ResourceHandlingState::handle(){
    //si on peut payer et joueurs présents sur case
    std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
    game->transitionTo(new OpponentChoiceState);


    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
}

