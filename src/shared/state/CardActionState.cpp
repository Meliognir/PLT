#include "CardActionState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include "CaptainDiceState.h"
#include <iostream>
#include <SFML/System/Time.hpp>

state::CardActionState::~CardActionState(){
    std::cout <<"destructor called"<< std::endl;
}

int pap=0;
void state::CardActionState::handle(){

    if (pap>game->getPlayerList().size()*3) {
        pap+=1;
        //en fin de tour, on passe au prochain tour
        std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
        game->transitionTo(new CaptainDiceState);
    }

    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);


}
