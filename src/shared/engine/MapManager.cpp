#include "MapManager.h"
#include "ResourceManager.h"
#include "../state.h"

#include "time.h" // to delay some steps and leave time to display


#define FORWARD 1
#define BACKWARD -1

namespace engine {

void MapManager::movePlayer(state::Player *player, int direction, int value)
{
    ResourceManager resourceManager2;
    state::Tile * currentTile = state::Game::map->listOfTiles.at(player->getPosition());
    int nextPosition = player->getPosition()+value*direction;
    int nextPath = player->getPath();
    /*
    if (Map->path1.at(nextPosition).isForking()){
        nextPath = InputHandler::pick_a_path();
    }*/
    player->setPosition(nextPosition);
    player->setPath(nextPath);
    state::Tile * nextTile = state::Game::map->listOfTiles.at(nextPosition);
    //wait for a while (display state in another thread);
    
    // recursiveMoveBack(player, nextPosition);
    if (resourceManager2.checkBankrupt(player, nextTile->tileResourceType, nextTile->tileCost)){
        moveOneTileBack(player);
    }
    




   // check le prix de la case et comparer avec les ressources
   // check bankrupt

   // si bankrupt :
        // payer tout
        // reculer

        // recommencer
        // fin

   // sinon :
        // check opponents

        // si opponents
            // duel
        
        // check le prix de la case et comparer avec les ressources

        // si bankrupt :
            // payer tout
            // reculer

            // recommence
            // FIN
        
        // sinon :
            // payer

            // FIN




    
}

void MapManager::moveOneTileBack(state::Player *player)
{
    movePlayer(player, BACKWARD, 1);    
}

bool MapManager::hasFork(int pos1, int pos2){
    int out = 0;
    int direction = 1;
    if (pos2 < pos1){
        int temp = pos2;
        pos2 = pos1;
        pos1 = temp;
        direction = -1;
    }
    int i;
    for (i=pos1; i<pos2; i++){
        out = out || state::Game::map->hasFork(i, direction);
    }
    return out;
}

}