#include "ResourceHandlingState.h"
#include "Game.h"
#include "CardActionState.h"
#include "OpponentChoiceState.h"
#include <iostream>
#include "Map.h"


state::ResourceHandlingState::~ResourceHandlingState(){
    std::cout <<"destructor called"<< std::endl;
}


void state::ResourceHandlingState::handle(){
    //si on peut payer et joueurs présents sur case
    int quantityResource=0;
    bool duel=false;

    /*A DEPLACER : */game->setActivePlayer(game->getPlayerList().at(game->getActivePlayerIndex()));

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

