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

namespace state {
    GameOverState::~GameOverState () {

    }

    void GameOverState::handle1() {
        int playerScore=0;
       //quand un joueur atteint la dernière case chaque joueur fini son tour et on compte alors les points
        for(Player * playerEnd : game->getPlayerList()) {
            int positionEnding=playerEnd->getPosition();
            if (positionEnding<=game->map->listOfTiles.end-7) {
                int playerScore=0;
                playerScore-=5;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //case -6
            if (positionEnding==game->map->listOfTiles.end-6) {
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //case -5
            if (positionEnding==game->map->listOfTiles.end-5) {
                playerScore+=1;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //case -4
            if (positionEnding==game->map->listOfTiles.end-4) {
                playerScore+=3;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //case -3
            if (positionEnding==game->map->listOfTiles.end-3) {
                playerScore+=5;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //case -2
            if (positionEnding==game->map->listOfTiles.end-2) {
                playerScore+=7;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile -1
            if (positionEnding==game->map->listOfTiles.end-1) {
                playerScore+=10;
                for (BoatHold *currentBoathold : playerEnd->getBoatHolds()) {
                    if (currentBoathold->hasResourceType("Gold")) {
                        playerScore+=currentBoathold->getQuantity();
                    }
                }
                std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << " ."<< std::endl;
            }
            //tile fin
            if (positionEnding==game->map->listOfTiles.end) {
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
}