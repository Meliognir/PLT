#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include <iostream>
#include "Map.h"

#define RESOURCE_HANDLING_STATE 4

namespace state {

void ResourceHandlingState::handle(){

    int quantityResource = 0;
    bool duel = false;
    int boatholdIndex;
    Player * activePlayer = game->getActivePlayer();
    int activePlayerPos = activePlayer->getPosition();
    std::string resourceToPay = game->map->getResourceType(activePlayerPos);
    int resourceToPayCost = game->map->getResourceCost(activePlayerPos);

    std::cout <<"coucou\r\n"<< std::endl;
    // activeplayer's total resource quantity he can pay for resource1
    for (BoatHold *bh : activePlayer->getBoatHolds()) {
        if (bh->hasResourceType(resourceToPay)) {
            quantityResource += bh->getQuantity();
        }
    }
    // checks activeplayer's opponent presence
    for (Player *player : game->getPlayerList()) {
        if (player->getPosition() == activePlayerPos) {
            duel = true;
        }
    }
    // don't forget to check path
    if(resourceToPayCost <= quantityResource){
        activePlayer->setBankrupt(false);
        if (duel){
            std::cout <<"si pas bankrupt si duel\r\n"<< std::endl;
            std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
            game->transitionTo(new OpponentChoiceState);
            notifyObservers();
        }
        else{
            std::cout <<"si pas bankrupt si pas duel\r\n"<< std::endl;
            boatholdIndex = activePlayer->getChosenBoatholdIndex();
            activePlayer->removeFromBoatHold(boatholdIndex, resourceToPayCost);
            std::cout <<"si pas bankrupt si pas duel fin\r\n"<< std::endl;
            std::cout <<"Transitioning to CardActionState state..."<< std::endl;
            game->transitionTo(new CardActionState);
            notifyObservers();          
        }
    }
    else{
        std::cout <<"si bankrupt pas duel\r\n"<< std::endl;
        activePlayer->setBankrupt(true);
        // pas de duel
        // payer au max
        // reculer jusqu'à payer tout
    }
    
    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
    notifyObservers();
}


ResourceHandlingState::~ResourceHandlingState(){
    std::cout <<"destructor called"<< std::endl;
}

int ResourceHandlingState::getStateId(){
    return RESOURCE_HANDLING_STATE;
}


}