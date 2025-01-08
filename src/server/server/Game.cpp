#include "Game.h"
#include <memory>
#include <map>
#include <vector>
#include <set>
#include "../../shared/state.h"
#include "../../shared/engine.h"

using namespace server;
using namespace std;
using std::unique_ptr;
using std::map;
using std::vector;

state::State* gameState = new state::GameConfigState();

Game::Game() : engine(*engine::GameEngine::getInstance(gameState)) {}


User* Game::getPlayerById (int id){
    auto it = players.find(id);
    if (it == players.cend())
        return nullptr;
    return it->second.get();
};

GameStatus Game::getStatus(){
    if(players.size() == 2) return RUNNING;
    return CREATING;
}

engine::GameEngine* Game::getEngine(){
    return &engine;
}

const std::map<int, std::unique_ptr<User>>& Game::getPlayers() const {
    return players;
}

void Game::modifyPlayer (int id, std::unique_ptr<User> newData){
    players[id] = move(newData);
    if (id > baseId) baseId = id;
}

void Game::removePlayer (int id){
    auto it = players.find(id);
    if (it == players.end())
        return;
    players.erase(it);
}

int Game::addPlayer (std::unique_ptr<User> newPlayer){
    int id = baseId;
    players.insert(std::make_pair(id, std::move(newPlayer)));
    baseId += 1;
    return id;
}