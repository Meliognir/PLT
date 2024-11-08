#include "Player.h"
#include "ActionCard.h"
#include "BoatHold.h"
#include <iostream>
namespace state{


Player::Player(int playerId, std::string name) : playerId(playerId), name(name)/*, boatHolds(6)*/{
}

BoatHold *Player::selectBoatHold(std::unique_ptr<Resources> resource){
    int index = 0;
      std::string input;

      while (true) {
        std::cout << "Choisissez un BoatHold (1-6) : ";
        std::cin >> index;

        if (index < 1 || index > 6) {
          std::cout << "Index invalide. Veuillez entrer un numéro entre 1 et 6.\n";
          continue;
        }

        BoatHold& selectedHold = boatHolds[index - 1];
        if (selectedHold.hasResourceType(resource->getType())) {
          std::cout << "Ce BoatHold contient déjà des ressources du même type.\n";
          continue; 
        }

        if (!selectedHold.isEmpty()) {
          std::cout << "Ce BoatHold contient d'autres ressources. Voulez-vous les remplacer ? (o/n) : ";
          std::cin >> input;

          if (input != "o") {
            continue; 
          }
          int quantityToRemove = selectedHold.getQuantity();
          selectedHold.removeResource(quantityToRemove);
        }
        return &selectedHold;
      }
}

void Player::addResourcesToBoatHold(std::unique_ptr<Resources> resource, int amount){
    BoatHold *selectedBoatHold = selectBoatHold(std::move(resource));
    if (selectedBoatHold != nullptr){
        selectedBoatHold->addResource(std::move(resource), amount);
        std::cout << "Ressource ajoutée au BoatHold avec succès !\n";
    }
}

Player::~Player()
{
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

const std::vector<ActionCard> &Player::getActionCards() const{
    return actionCards;
}

void Player::setActionCards(const std::vector<ActionCard> &actionCard){
    this->actionCards=actionCard;
}

const std::string &Player::getName() const
{
    return name;
}

void Player::setName(const std::string &name){
    this->name=name;
}
}