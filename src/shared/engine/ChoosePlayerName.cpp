#include "ChoosePlayerName.h"

engine::ChoosePlayerName::ChoosePlayerName(int player, std::string name) : playerIndex(player), name(name){
}

void const engine::ChoosePlayerName::launchCommand (state::Game * GamePtr) {
    state::Player* player = GamePtr->getPlayerList().at(playerIndex);
    player->setName(name);
}

engine::ChoosePlayerName::~ChoosePlayerName(){}