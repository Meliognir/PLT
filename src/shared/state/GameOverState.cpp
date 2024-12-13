//
// Nathan work here
//

#include "GameOverState.h"
#include "BoatHold.h"
#include <list>
#include <unicode/urename.h>
#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Map.h"

#define GAME_OVER_STATE 9

namespace state {

    void GameOverState::handle() {
        int playerScore=0;
       //quand un joueur atteint la dernière tile chaque joueur fini son tour et on compte alors les points
        for(Player * playerEnd : game->getPlayerList()) {
            int positionEnding=playerEnd->getPosition();
            if (positionEnding <= game->map->getSize()-7) {
                int playerScore=0;
                playerScore-=5;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -6
            if (positionEnding==game->map->getSize()-6) {
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -5
            if (positionEnding==game->map->getSize()-5) {
                playerScore+=1;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -4
            if (positionEnding==game->map->getSize()-4) {
                playerScore+=3;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -3
            if (positionEnding==game->map->getSize()-3) {
                playerScore+=5;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -2
            if (positionEnding==game->map->getSize()-2) {
                playerScore+=7;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -1
            if (positionEnding==game->map->getSize()-1) {
                playerScore+=10;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile fin
            if (positionEnding==game->map->getSize()) {
                playerScore+=15;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
        }
    }

    int GameOverState::getStateId (){
        return GAME_OVER_STATE;
    }

    GameOverState::~GameOverState () {

    }
}