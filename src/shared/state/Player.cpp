#include "Player.h"
namespace state{
int Player::getPlayerId() const{
    return playerId;
}

void Player::setPlayerId(int playerId){
    this->playerId=playerId;
}

const std::string &Player::getName() const
{
    return name;
}

void Player::setName(const std::string &name){
    this->name=name;
}
}