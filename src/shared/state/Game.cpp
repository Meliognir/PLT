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

void state::Game::request(){
    this->state->handle();
}
