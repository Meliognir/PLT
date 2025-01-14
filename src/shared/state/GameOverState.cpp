//
// Nathan work here
//

#include "GameOverState.h"
#include "GameConfigState.h"
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
        int maxScore = -50;
        int mapSize = game->map->getSize();
        int positionEnding;
        int relativePosition;
        int playerScore;
        for(Player * playerEnd : game->getPlayerList()) {
            positionEnding=playerEnd->getPosition();
            relativePosition = positionEnding-mapSize;
            playerScore = 0;
            for(BoatHold *currentBoathold : playerEnd->getBoatHolds()){
                if (currentBoathold->hasResourceType("Gold")) {
                    playerScore += currentBoathold->getQuantity();
                }
            }
            if (relativePosition <= -15) {
                playerScore -= 5;
            }
            else {
                if (relativePosition == 0){
                    playerScore += 15;
                }
                    else{

                    switch (relativePosition) {
                        case -6:
                            playerScore += 0;
                            break;
                        case -5:
                            playerScore += 1;
                            break;
                        case -4:
                            playerScore += 3;
                            break;
                        case -3:
                            playerScore += 5;
                            break;
                        case -2:
                            playerScore += 7;
                            break;
                        case -1:
                            playerScore += 10;
                            break;
                        default:
                            break;
                    }
                }
            }
            std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << "."<< std::endl;
            if(playerScore > maxScore){
                maxScore = playerScore;
                winner = playerEnd;
            }
        }
        std::cout<< "Player : " << winner->getName() << " has won with a score of : " << maxScore << "."<< std::endl;
        game->setGameOver(false);
        game->transitionTo(new GameConfigState);
        return;
    }

    int GameOverState::getStateId (){
        return GAME_OVER_STATE;
    }

    GameOverState::~GameOverState () {

    }
}