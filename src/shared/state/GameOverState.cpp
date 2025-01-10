//
// Nathan work here
//

#include "GameOverState.h"
#include "BoatHold.h"
#include <list>
#include <unicode/urename.h>
#include "Observable.h"
#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Map.h"

#define GAME_OVER_STATE 9

namespace state {

    void GameOverState::handle() {
        //quand un joueur atteint la dernière tile chaque joueur fini son tour et on compte alors les points
        Player * winner;
        int maxScore = 0;

        for(Player * playerEnd : game->getPlayerList()) {
            int positionEnding=playerEnd->getPosition();
            int bhGold = 0;
            int playerScore = 0;
            for(BoatHold *currentBoathold : playerEnd->getBoatHolds()){
                if (currentBoathold->hasResourceType("Gold")) {
                    bhGold += currentBoathold->getQuantity();
                }
            }
            if (positionEnding <= game->map->getSize() - 7) {
                playerScore -= 5;
            } else {
                int relativePosition = game->map->getSize() - positionEnding;

                switch (relativePosition) {
                    case 6:
                        playerScore += 0;
                        break;
                    case 5:
                        playerScore += 1;
                        break;
                    case 4:
                        playerScore += 3;
                        break;
                    case 3:
                        playerScore += 5;
                        break;
                    case 2:
                        playerScore += 7;
                        break;
                    case 1:
                        playerScore += 10;
                        break;
                    case 0:
                        playerScore += 15;
                        break;
                    default:
                        break;
                }
            }
            playerScore+=bhGold;
            std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << "."<< std::endl;
            if(playerScore > maxScore){
                maxScore = playerScore;
                winner = playerEnd;
            }
        }
        std::cout<< "Player : " << winner->getName() << " has won with a score of : " << maxScore << "."<< std::endl;
        game->setGameOver(false);
        return;
    }

    int GameOverState::getStateId (){
        return GAME_OVER_STATE;
    }

    GameOverState::~GameOverState () {

    }
}