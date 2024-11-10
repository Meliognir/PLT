#include "Player.h"
#include "Game.h"
#include "ActionCard.h"
#include "BoatHold.h"
#include <iostream>

namespace state{


Player::Player(int playerId, std::string name) : playerId(playerId), name(name){
}

Player::~Player(){
}

BoatHold *Player::selectBoatHold(std::unique_ptr<Resources> resource){
    int index = 0;
    std::string input;

    while (true) {
    std::cout << "Vous avez 6 BoatHold. Choisissez-en un (1-6) : ";
    std::cin >> index;

    if (index < 1 || index > 6) {
        std::cout << "Index invalide. Veuillez entrer un numéro entre 1 et 6.\n";
        continue;
    }

    BoatHold& selectedHold = boatHolds[index - 1];
    if (selectedHold.hasResourceType(resource->getType())) {
        std::cout << "Ce BoatHold contient déjà des ressources du même type. Choisir un BoatHold vide ou ayant des ressources de type différent.\n";
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

bool Player::chooseTimeDice(int dice1, int dice2){
    std::string input;
    while (true){
        std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n" << "dé 1 : " << dice1 << " dé 2 : " << dice2 << std::endl;
        std::cin >> input;
        if (input == "1" || input == "2"){
            break;
        } else {
            std::cout << "Entrée invalide. Veuillez entrer '1' ou '2'.\n";
        }
    }
    if (input == "1"){
        std::cout << "Le dé " << dice1 << " sera le dé du jour. Le dé " << dice2 << " sera le dé de la nuit." << std::endl;
        return true;
    } else {
        std::cout << "Le dé " << dice2 << " sera le dé du jour. Le dé " << dice1 << " sera le dé de la nuit." << std::endl;
        return false;
    }
}

void Player::chooseCard(){
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

const std::string &Player::getName() const{
    return name;
}

void Player::setName(const std::string &name){
    this->name=name;
}

const std::vector<Treasure> &Player::getTreasures() const{
    return treasures;
}

void Player::setTreasures(const std::vector<Treasure> &treasures){
    this->treasures= treasures;
}

const std::vector<BoatHold> &Player::getBoatHolds() const{
    return boatHolds;
}

void Player::setBoatHolds(const std::vector <BoatHold>& boatHolds){
    this->boatHolds = boatHolds;
}

/*
const std::vector<ActionCard> &Player::getActionCards() const{
    return actionCards;
}

void Player::setActionCards(const std::vector<ActionCard> &actionCard){
    this->actionCards=actionCard;
}*/

}