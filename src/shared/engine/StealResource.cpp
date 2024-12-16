#include "StealResource.h"
#include "state.h"
namespace engine{
//TODO

StealResource::StealResource(int boatholdIndex, int winnerIndex, int loserIndex ) : winnerIndex(winnerIndex), loserIndex(loserIndex), boatholdIndex(boatholdIndex){
}

void const StealResource::launchCommand(state::Game * GamePtr){
    state::Player* winner = GamePtr->getPlayerList()[winnerIndex];
    state::Player* loser = GamePtr->getPlayerList()[loserIndex];
    //winner->addResourcesToBoatHold(resourceType, boathold, quantity, 0);
    // je le ferai plus tard
}

StealResource::~StealResource(){}

}
