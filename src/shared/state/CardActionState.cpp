#include "CardActionState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include "CaptainDiceState.h"
#include <iostream>
#include <SFML/System/Time.hpp>

state::CardActionState::~CardActionState(){
    std::cout <<"destructor called"<< std::endl;
}

int pap = 0;
int gameTurn = 0;

void state::CardActionState::handle(){

    if (pap > game->getPlayerList().size()*3) {
        pap+=1;
        
        //update of Captain player
        gameTurn++; 
        game->setTurn(gameTurn);
        int captainIndex = game->getCaptainIndex();
        captainIndex = (captainIndex + 1) % game->getPlayerList().size();
        game->setCaptainIndex(captainIndex);
        game->setActivePlayer(game->getPlayerList().at(captainIndex));
        std::cout << "Starting a new round in the Playerlist." << std::endl;
        
        //end of turn
        std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
        game->transitionTo(new CaptainDiceState);
    }

    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);

}
