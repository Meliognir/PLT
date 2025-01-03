#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include "Observable.h"
#include <iostream>
#include "Map.h"

#define RESOURCE_HANDLING_STATE 4

namespace state {

void ResourceHandlingState::handle(){

    int nbOpponent = 0;
    Player *activePlayer = game->getActivePlayer();
    
    std::cout <<"coucou\r\n"<< std::endl;

    //player's total resource quantity he can pay for resourcetoPayType
    int activePlayerPos = activePlayer->getPosition();
    std::string resourceToPayType = game->map->getResourceType(activePlayerPos);
    int resourceToPayCost = game->map->getResourceCost(activePlayerPos);
    int quantityResource = 0;
    for (BoatHold *bh : activePlayer->getBoatHolds()) {
        if (bh->hasResourceType(resourceToPayType)) {
            quantityResource += bh->getQuantity();
        }
    }
    std::cout <<"player: " << activePlayer->getName() << " has: " << quantityResource << " " << resourceToPayType << "\r\n"<< std::endl;
    std::cout <<"the tile costs: " << resourceToPayCost << " " << resourceToPayType << "\r\n"<< std::endl;

    //player can't pay
    while(quantityResource < resourceToPayCost){
        
        //player pays as much as he can afford
        activePlayer->setResTypeToPay(resourceToPayType);
        activePlayer->setAmountToPay(quantityResource);
        activePlayer->setHasToPay(true);

        //player moves backward
        activePlayer->moveWithDirection(1, -1);
        activePlayer->setPrevDuel(false);

        //player's total resource quantity he can pay for resourcetoPayType
        activePlayerPos = activePlayer->getPosition();
        resourceToPayType = game->map->getResourceType(activePlayerPos);
        resourceToPayCost = game->map->getResourceCost(activePlayerPos);
        quantityResource = 0;
        for (BoatHold *bh : activePlayer->getBoatHolds()) {
            if (bh->hasResourceType(resourceToPayType)) {
                quantityResource += bh->getQuantity();
            }
        }
        std::cout <<"player: " << activePlayer->getName() << " has: " << quantityResource << " " << resourceToPayType << "\r\n"<< std::endl;
        std::cout <<"the tile costs: " << resourceToPayCost << " " << resourceToPayType << "\r\n"<< std::endl;
    }

    //checks activeplayer's opponent presence
    for (Player *player : game->getPlayerList()) {
        if (player->getPosition() == activePlayerPos) {
            nbOpponent += 1;
        }
    }
    nbOpponent -= 1;
    std::cout <<"there are: " << nbOpponent << " opponents on this tile\r\n"<< std::endl;

    //condition for duel
    if(nbOpponent > 0 && !(activePlayer->getPrevDuel())){
        std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
        game->transitionTo(new OpponentChoiceState);
        notifyObservers();
    }
    //condition to exit ResourceHandlingState
    if(nbOpponent == 0 || activePlayer->getPrevDuel()){
        //player pays resourceToPayCost
        activePlayer->setResTypeToPay(resourceToPayType);
        activePlayer->setAmountToPay(resourceToPayCost);
        activePlayer->setHasToPay(true);
        std::cout <<"Transitioning to CardActionState state..."<< std::endl;
        game->transitionTo(new CardActionState);
        notifyObservers();  
    }
    
}

ResourceHandlingState::~ResourceHandlingState(){
    std::cout <<"destructor called"<< std::endl;
}

int ResourceHandlingState::getStateId(){
    return RESOURCE_HANDLING_STATE;
}

}