#include "GameEngine.h"
#include "../state.h"
#include "../state/GameOverState.h"
#include "../../client/client.h"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <utility>

engine::GameEngine::GameEngine(state::State *state){
    game = new state::Game(state);
}

void engine::GameEngine::initializeGame(int playerCount){

    game->request(); // Appelle GameConfigState pour initialiser les joueurs

}