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

    std::cout <<"coucou"<< std::endl;
    Player * activePlayer = game->getActivePlayer();
    std::string resource1 = game->map->getResourceType(activePlayer->getPosition());
    // activeplayer's total resource quantity he can pay for resource1
    for (BoatHold *bh : activePlayer->getBoatHolds()) {
        if (bh->hasResourceType(resource1)) {
            quantityResource += bh->getQuantity();
        }
    }
    // checks activeplayer's opponent presence
    for (Player *player : game->getPlayerList()) {
        if (player->getPosition() == activePlayer->getPosition()) {
            duel = true;
        }
    }
    // don't forget to check path
    if(game->map->getResourceCost(activePlayer->getPosition()) <= quantityResource){
        activePlayer->setBankrupt(false);
        if (duel){
            std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
            game->transitionTo(new OpponentChoiceState);
        }
        else{
            // payer direct
        }   
    }
    else{
        activePlayer->setBankrupt(true);
        // pas de duel
        // payer au max
        // reculer jusqu'à payer tout
    }
    
    std::cout <<"Transitioning to CardAction state..."<< std::endl;
    game->transitionTo(new CardActionState);
}


ResourceHandlingState::~ResourceHandlingState(){
    std::cout <<"destructor called"<< std::endl;
}

int ResourceHandlingState::getStateId(){
    return RESOURCE_HANDLING_STATE;
}


}