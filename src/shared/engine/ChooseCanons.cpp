#include "ChooseCanons.h"

engine::ChooseCanons::ChooseCanons(int player, int quantity) : playerIndex(player), quantity(quantity){
}

void const engine::ChooseCanons::launchCommand (state::Game * GamePtr){
    state::Player* player = GamePtr->getPlayerList()[playerIndex];
    player->setFirePower(quantity);
}

engine::ChooseCanons::~ChooseCanons(){}