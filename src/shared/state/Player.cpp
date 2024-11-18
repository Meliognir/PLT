#include "Player.h"
#include "Game.h"
#include "ActionCard.h"
#include "BoatHold.h"
#include "../../client/client/InputHandler.h"
#include "../engine/ResourceManager.h"
#include <iostream>
#include <memory>
#include "../../client/client/InputHandler.h"
#include <algorithm> // Pour std::shuffle
#include <random>   // Pour std::default_random_engine et std::random_device
#include <utility> // Pour std::forward

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

namespace state{


Player::Player(int playerId, std::string name) : playerId(playerId), name(name){
    for (int i = 0; i < 6; ++i) {
        boatHolds.push_back(new BoatHold());
}
}

Player::~Player(){
    for (BoatHold* hold : boatHolds) {
        delete hold; 
    }
    boatHolds.clear();
}

BoatHold *Player::selectBoatHold(const std::string& resourceType){
    client::InputHandler inputHandler;
    engine::ResourceManager resourceManager;
    if (!resourceManager.isBoatHoldAvailable(*this, resourceType)){
        inputHandler.displayMessage("All boatholds already have this resource. Cannot replace.");
        return nullptr;
    }
    while (true){
    int index = inputHandler.selectUserBoatHold(6); // TODO : nombre de boathold d'un player
    if (resourceManager.checkSameBoathold(*this,resourceType,index)){
        inputHandler.displayMessage("Boathold already contains this type of resource. Please choose another.");
        continue;
    }
    if (resourceManager.checkOccupied(*this, index)){
        if (!inputHandler.confirmBoatHoldReplace()){
            continue;
        }
    }
    BoatHold* selectedHold = resourceManager.selectBoathold(*this, resourceType, index);
    if (selectedHold == nullptr) {
        inputHandler.displayMessage("Error selecting BoatHold.");
        return nullptr;
    }
    return selectedHold;
    }
}

void Player::addResourcesToBoatHold(std::unique_ptr<Resources> resource, int amount, int skipSelection/*default value = 0*/)
{
    if (!resource) {
        std::cerr << "Erreur : le pointeur resource est nul !\n";
        return;
    }

    std::string resourceType = resource->getType();
    BoatHold *selectedBoatHold;

    if (skipSelection){
        selectedBoatHold = boatHolds.at(skipSelection-1);
    }
    else {
        selectedBoatHold = selectBoatHold(resourceType);
    }

    if (selectedBoatHold != nullptr){
        selectedBoatHold->addResource(std::move(resource), amount);
        std::cout << "Ressource ajoutée au BoatHold avec succès !\n";
    }
    else{
        selectedBoatHold = selectBoatHold(resourceType);
        if (selectedBoatHold != nullptr){
            selectedBoatHold->addResource(std::move(resource), amount);
            std::cout << "Ressource ajoutée au BoatHold avec succès !\n";
        }
        else{
            std::cout << "La ressource n'a pas pu ếtre ajoutée.\n";
        }
    }
}

// shuffles player cardDeck
void Player::shuffleDeck(){ 
    std::random_device rd;
    // Mersenne Twister PRNG initialisé avec r
    std::mt19937 g(rd());
    std::shuffle(cardDeck.begin(), cardDeck.end(), g);
}

// sets activeCard to player's choice
void Player::chooseCard(){
    client::InputHandler inputHandler;
    
    inputHandler.displayMessage("Your 3 handCards : ");
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }
    int choice = 0;
    while (true) {
        inputHandler.displayMessage("Choose a card, enter an index between 1 and 3 : ");
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            inputHandler.displayMessage("Non valid entry.");
        } else {
            try {
                activeCard = handCards.at(choice - 1);
                inputHandler.displayMessage("You chose card with ID : " + std::to_string(activeCard));
                break;
            } catch (const std::out_of_range& e) {
                inputHandler.displayMessage("Error in handCards : Index beyond limits.");
            }
        }
    }
}

void Player::playTurn(){
    //day action
    //night action
    //check pour shuffle
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

const std::vector<BoatHold *> &Player::getBoatHolds() const{
    return boatHolds;
}

void Player::setBoatHolds(const std::vector <BoatHold *>& boatHolds){
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