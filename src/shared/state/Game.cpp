#include "Game.h"
namespace state{
void Game::gameTurn(int time){

}

Game::Game(State *state, std::vector<Player *> playerList)
{
    this->transitionTo(state);
}

Game::~Game(){
    delete state;
}

void Game::transitionTo(State *state){
    if (this->state != nullptr){
        delete this->state;
    }
    this->state=state;
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

}