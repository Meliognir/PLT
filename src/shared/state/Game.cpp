#include "Game.h"

void state::Game::gameTurn(int time){

}

state::Game::Game(State *state, std::vector<Player *> playerList)
{
    this->transitionTo(state);
}

state::Game::~Game(){
    delete state;
}

void state::Game::transitionTo(State *state){
    if (this->state != nullptr){
        delete this->state;
    }
    this->state=state;
    this->state->setContext(this);
}

void state::Game::request1(){
    this->state->handle1();
}

void state::Game::request2(){
    this->state->handle2();
}
void state::Game::setTurn(int turn){
}

const std::vector<state::Player *> &state::Game::getPlayerList() const{
    return this->playerList;
}

void state::Game::setPlayerList(const std::vector<Player *> &playerList){
    this->playerList=playerList;
}
