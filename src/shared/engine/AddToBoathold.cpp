#include "AddToBoathold.h"
#include "state.h"

void const engine::AddToBoathold::launchCommand(state::Game *GamePtr){
    state::Player* player = GamePtr->getPlayerList()[playerIndex];
    player->addResourcesToBoatHold(resourceType, boathold, quantity);
}

engine::AddToBoathold::AddToBoathold(int player, int boathold, int quantity, std::string resourceType) : playerIndex(player), boathold(boathold), quantity(quantity), resourceType(resourceType){
}

engine::AddToBoathold::~AddToBoathold(){}