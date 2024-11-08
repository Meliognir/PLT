#include "Game.h"
namespace state{
void Game::gameTurn(int time){

}

Game::Game(State *state, Map *map)
{
    this->transitionTo(state);
    this->map = map;
}

Game::~Game(){
    delete map;
    delete state;
    for(Player* player : playerList){
        delete player;
    }
    playerList.clear();
}

void Game::transitionTo(State *state){
    if (this->state != nullptr){
        delete this->state;
    }
    this->state = state;
    this->state->setContext(this);
}

void Game::request1(){
    this->state->handle1();
}

void Game::request2(){
    this->state->handle2();
}
void Game::setTurn(int turn){
}

const std::vector<Player *> &Game::getPlayerList() const{
    return this->playerList;
}

void Game::displayState()
{
    // Ecran principal avec la map et la position des joueurs
    int mapSize = map->getSize();
    printf("Affichage de la map :\n");
    for (int i = 0; i < mapSize; i++){
        printf("Affichage de la tuile i\n");
    }

    // Ecran dédié aux états actuels des joueurs et les ressources dans leur cale
    int numberOfPlayers = getPlayerList().size();
    for (int i = 0; i < numberOfPlayers; i++){
        printf("Affichage des informations du i-ème joueur\n");
    }
}

void Game::setPlayerList(const std::vector<Player *> &playerList){
    this->playerList=playerList;
}

bool Game::checkGameEndCondition(){
    for (Player* player : playerList) {
        if(player->getPreviousPosition() < map->getSize() && player->getPosition() >= map->getSize()){
            return true;
        }
    }
}

}