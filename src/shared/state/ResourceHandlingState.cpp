#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include <iostream>
#include "Map.h"

#define RESOURCE_HANDLING_STATE 4

namespace state {

void ResourceHandlingState::handle(){
    //si on peut payer et joueurs présents sur case
    int quantityResource=0;
    bool duel=false;

    std::cout <<"coucou"<< std::endl;
    Player * activePlayer=game->getActivePlayer();
    std::string resource1=game->map->getResourceType(activePlayer->getPosition());
    for (BoatHold *currentBoathold : activePlayer->getBoatHolds()) {
        if (currentBoathold->hasResourceType(resource1)) {
            quantityResource+=currentBoathold->getQuantity();
        }
    }
    for (Player *player : game->getPlayerList()) {
        if (player->getPosition()==activePlayer->getPosition()) {
            duel=true;
        }
    }
    //check path
    if (game->map->getResourceCost(activePlayer->getPosition())<=quantityResource && duel){
        std::cout <<"Transitioning to OpponentChoice state..."<< std::endl;
        game->transitionTo(new OpponentChoiceState);
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