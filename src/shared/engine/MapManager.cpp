#include "MapManager.h"
#include "ResourceManager.h"
#include "../state.h"

#include "time.h" // to delay some steps and leave time to display


#define FORWARD 1
#define BACKWARD -1

namespace engine {

// > prio pas ordre
//pas d'argent > combat > payer

MapManager::MapManager()
{
}

void MapManager::movePlayer(state::Player *player, int direction, int value)
{
    //ResourceManager resourceManager2;
    //state::Tile * currentTile = state::Game::map->listOfTiles.at(player->getPosition() % map.getSize());
    int nextPosition = player->getPosition()+value*direction;
    int nextPath = player->getPath();
    
    int lastTile = mapPtr->getSize()-1;
    if (nextPosition > lastTile) nextPosition = lastTile;
    /*
    if (Map->path1.at(nextPosition % map.getSize()).isForking()){
        nextPath = InputHandler::pick_a_path();
    }*/
    
    player->setPosition(nextPosition);
    player->setPath(nextPath);
}
    // recursiveMoveBack(player, nextPosition);
    /*
    if (resourceManager2.checkBankrupt(player, nextTile->tileResourceType, nextTile->tileCost)){
        //pay resource;
        moveOneTileBack(player);
    }
    else {
        //pay resource;
        return;
    }
    */
    
   // check le prix de la case et comparer avec les ressources
   // check bankrupt

   // si bankrupt :
        // payer tout
        // reculer
        // (attention aux forks, exception et passage par le client)

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
            // (attention aux forks, exception et passage par le client)

            // recommence
            // FIN
        
        // sinon :
            // payer

            // FIN




    
//}

void MapManager::moveOneTileBack(state::Player *player)
{
    movePlayer(player, BACKWARD, 1);    
}

void MapManager::setMapPtr(state::Map *mapPtr)
{
    mapPtr = mapPtr;
}

state::Map *MapManager::getMapPtr()
{
    return mapPtr;
}

MapManager::~MapManager()
{
}


/*A ne pas supprimer si on met les fork :
 *bool MapManager::hasFork(int pos1, int pos2){
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
*/
}