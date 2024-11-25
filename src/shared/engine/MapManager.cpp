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
    //wait for a while (display state in another thread);
    
    /*
    if (checkPriceAndBoatHolds()){
        moveOneTileBack(state::Player *);
    }
    */




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

}