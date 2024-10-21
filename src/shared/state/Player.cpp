#include "Player.h"

const std::string &state::Player::getName() const{
    return name;
}

void state::Player::setName(const std::string &name){
    this->name=name;
}
