#include "Player.h"

int state::Player::getPlayerId() const{
    return playerId;
}

void state::Player::setPlayerId(int playerId){
    this->playerId=playerId;
}

const std::string &state::Player::getName() const
{
    return name;
}

void state::Player::setName(const std::string &name){
    this->name=name;
}
