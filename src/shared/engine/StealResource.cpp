#include "StealResource.h"
#include "../state/BoatHold.h"
#include "state.h"

namespace engine{

StealResource::StealResource(int boatholdIndex, int winnerIndex, int loserIndex) : boatholdIndex(boatholdIndex), winnerIndex(winnerIndex), loserIndex(loserIndex){}

void const StealResource::launchCommand(state::Game * GamePtr){
    state::Player* winner = GamePtr->getPlayerList()[winnerIndex];
    state::Player* loser = GamePtr->getPlayerList()[loserIndex];
    state::BoatHold *stolenHold = loser->getBoatHolds().at(boatholdIndex);
    std::string resourceType = stolenHold->getResourceType();
    int quantity = stolenHold->getQuantity();;
    winner->addResourcesToBoatHold(resourceType, boatholdIndex, quantity, 0);
    loser->removeFromBoatHold(boatholdIndex, quantity);
}

StealResource::~StealResource(){}

}
