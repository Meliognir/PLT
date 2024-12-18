#include "CardActionState.h"
#include "Game.h"
#include "ResourceHandlingState.h"
#include "CaptainDiceState.h"
#include <iostream>
#include <SFML/System/Time.hpp>

#define CARD_ACTION_STATE 3

int gameTurn = 0;

namespace state {
void CardActionState::handle(){

    int actionCounter = game->actionCounter;
    /*
    int playerNb = game->getPlayerList().size();
    int activePlayerIndex = game->getActivePlayerIndex();
    int captainIndex = game->getCaptainIndex();
    activePlayerIndex = (captainIndex + 1);
    game->setActivePlayerIndex(activePlayerIndex);
    game->setActivePlayer(game->getPlayerList().at(activePlayerIndex));
    */

    //fin des actions de tous les joueurs
    if(actionCounter > game->getPlayerList().size()*3) {
        
        //update of Captain player
        /*
        gameTurn++; 
        game->setTurn(gameTurn);
        game->setActivePlayerIndex(0);
        int captainIndex = game->getCaptainIndex();
        captainIndex = (captainIndex + 1) % playerNb;
        game->setCaptainIndex(captainIndex);
        game->setActivePlayer(game->getPlayerList().at(captainIndex));
        std::cout << "Starting a new round in the Playerlist." << std::endl;
        */

        //end of turn
        std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
        game->transitionTo(new CaptainDiceState);
    }

    std::cout <<"Transitioning to ResourceHandling state..."<< std::endl;
    game->transitionTo(new ResourceHandlingState);

}

int CardActionState::getStateId(){
    return CARD_ACTION_STATE;
}

CardActionState::~CardActionState(){
    std::cout <<"destructor called"<< std::endl;
}

}