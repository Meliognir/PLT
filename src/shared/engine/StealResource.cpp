#include "StealResource.h"
#include "../state/BoatHold.h"
#include "state.h"

namespace engine{

StealResource::StealResource(int stolenBoatholdId, int winnerIndex, int loserIndex, int winnerBoatholdId) : stolenBoatholdId(stolenBoatholdId), winnerIndex(winnerIndex), loserIndex(loserIndex), winnerBoatholdId(winnerBoatholdId){}

void const StealResource::launchCommand(state::Game * GamePtr){
    state::Player* winner = GamePtr->getPlayerList()[winnerIndex];
    state::Player* loser = GamePtr->getPlayerList()[loserIndex];
    state::BoatHold *stolenHold = loser->getBoatHolds().at(stolenBoatholdId);
    std::string resourceType = stolenHold->getResourceType();
    int quantity = stolenHold->getQuantity();
    winner->addResourcesToBoatHold(resourceType, winnerBoatholdId, quantity, 0);
    loser->removeFromBoatHold(stolenBoatholdId, quantity);
}

StealResource::~StealResource(){}

}
