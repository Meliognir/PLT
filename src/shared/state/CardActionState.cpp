#include "CardActionState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include "CaptainDiceState.h"
#include <iostream>
#include <SFML/System/Time.hpp>

state::CardActionState::~CardActionState(){
    std::cout <<"destructor called"<< std::endl;
}

unsigned pap = 0;
int gameTurn = 0;

void state::CardActionState::handle(){

    int playerNb = game->getPlayerList().size();
    int activePlayerIndex = game->getActivePlayerIndex();
    int captainIndex = game->getCaptainIndex();
    activePlayerIndex = (captainIndex + 1);
    game->setActivePlayerIndex(activePlayerIndex);
    game->setActivePlayer(game->getPlayerList().at(activePlayerIndex));

    //fin des actions de tous les joueurs
    if(pap > game->getPlayerList().size()*3) {
        pap+=1;
        
        //update of Captain player
        gameTurn++; 
        game->setTurn(gameTurn);
        game->setActivePlayerIndex(0);
        int captainIndex = game->getCaptainIndex();
        captainIndex = (captainIndex + 1) % playerNb;
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
