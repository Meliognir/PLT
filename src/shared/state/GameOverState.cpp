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
        game->setGameOver(false);
        game->transitionTo(new GameConfigState);
        notifyObservers();
        return;
    }

    int GameOverState::getStateId (){
        return GAME_OVER_STATE;
    }

    GameOverState::~GameOverState () {

    }
}