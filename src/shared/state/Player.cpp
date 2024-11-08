#include "Player.h"
#include "ActionCard.h"
#include "BoatHold.h"
namespace state{


Player::Player(int playerId, std::string name) : playerId(playerId), name(name)/*, boatHolds(6)*/{
}

Player::~Player(){
}

int Player::getPlayerId() const{
    return playerId;
}

void Player::setPlayerId(int playerId){
    this->playerId=playerId;
}

int Player::getPosition() const{
    return position;
}

void Player::setPosition(int position){
    this->position=position;
}

const std::vector<Treasure> &Player::getTreasures() const{
    return treasures;
}

void Player::setTreasures(const std::vector<Treasure> &treasures){
    this->treasures= treasures;
}

const std::vector<ActionCard> &Player::getActionCard() const{
    return actionCard;
}

void Player::setActionCard(const std::vector<ActionCard> &actionCard){
    this->actionCard=actionCard;
}

const std::string &Player::getName() const
{
    return name;
}

void Player::setName(const std::string &name){
    this->name=name;
}
}