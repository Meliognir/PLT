#include "ChoosePath.h"

engine::ChoosePath::ChoosePath(int player, int path) : playerIndex(player), path(path){

}

void const engine::ChoosePath::launchCommand (state::Game * GamePtr) {
    state::Player* player = GamePtr->getPlayerList().at(playerIndex);
    player->setPath(path);
}

engine::ChoosePath::~ChoosePath(){}