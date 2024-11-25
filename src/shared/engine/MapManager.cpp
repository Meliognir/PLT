#include "MapManager.h"
#include "ResourceManager.h"
#include "time.h"

#define FORWARD 1
#define BACKWARD -1

namespace engine {

void MapManager::movePlayer(state::Player *player, int direction, int value)
{
    int nextPosition = player->getPosition()+value*direction;
    player->setPosition(nextPosition);
    
    //wait(5000);
    
}

void MapManager::moveOneTileBack(state::Player *player)
{
    movePlayer(player, BACKWARD, 1);    
}

}