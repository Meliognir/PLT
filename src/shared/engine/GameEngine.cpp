#include "GameEngine.h"
#include "MapManager.h"
#include "ResourceManager.h"
#include "../state.h"
#include "../state/GameOverState.h"
#include "../../client/client.h"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <utility>
namespace engine{
GameEngine* GameEngine::instance = nullptr;

GameEngine::GameEngine(state::State *state){
    game = new state::Game(state);
}

void GameEngine::initializeGame(int playerCount){

    game->request(); // Appelle GameConfigState pour initialiser les joueurs

}
GameEngine* GameEngine::getInstance(state::State* state) {
    if (instance == nullptr) {
        instance = new GameEngine(state);
    }
    return instance;
}

}