#include "Player.h"
#include "Game.h"
#include "State.h"
#include "ActionCard.h"
#include "BoatHold.h"
#include "../engine/ActionProcessor.h"
#include "../engine/CombatManager.h"
#include "../engine/ResourceManager.h"
#include "../../client/client/InputHandler.h"
#include <iostream>
#include <memory>
#include <algorithm> // Pour std::shuffle
#include <random>   // Pour std::default_random_engine et std::random_device
#include <utility> // Pour std::forward


/* -------------------------------------------- */
/* ------------Lucian works here -------------- */
/* -------------------------------------------- */

#define DAY true
#define NIGHT false

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

namespace state{


Player::Player(int playerId, std::string name) : playerId(playerId), name(name){
    for (int i = 0; i < 6; ++i) {
        boatHolds.push_back(new BoatHold());
    }
    cardDeck={0,1,2,3,4,5,6,7,8,9,10};
    shuffleDeck();
    for (int j = 0; j < 3; ++j) {
        moveCardToHand();
    }

}

Player::~Player(){
    for (BoatHold* hold : boatHolds) {
        delete hold; 
    }
    boatHolds.clear();
}

// refactored
BoatHold *Player::selectBoatHold(const std::string& resourceType){
    client::InputHandler inputHandler;// a vire
    engine::ResourceManager resourceManager;// a vire
    if (!resourceManager.isBoatHoldAvailable(this, resourceType)){
        std::cout<<"All boatholds already have this resource. Cannot replace."<<std::endl;
        return nullptr;
    }
    while (true){
    size_t index = inputHandler.selectUserBoatHold(6); // TODO : nombre de boathold d'un player
    if (resourceManager.checkSameBoathold(this,resourceType,index)){
        std::cout<<"Boathold already contains this type of resource. Please choose another."<<std::endl;
        continue;
    }
    if (resourceManager.checkOccupied(this, index)){
        if (!inputHandler.confirmBoatHoldReplace()){
            continue;
        }
    }
    BoatHold* selectedHold = resourceManager.selectBoathold(this, resourceType, index);
    if (selectedHold == nullptr) {
        std::cout<<"Error selecting BoatHold."<<std::endl;
        return nullptr;
    }
    return selectedHold;
    }
}

void Player::addResourcesToBoatHold(std::unique_ptr<Resources> resource, int amount, int skipSelection/*default value = 0*/) // engine
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
        std::cout << "Ressource ajoutée au BoatHold avec succès !\n"<< std::endl;
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

// refactored
// shuffles player cardDeck
void Player::shuffleDeck(){ 
    std::random_device rd;
    // Mersenne Twister PRNG initialisé avec r
    std::mt19937 g(rd());
    std::shuffle(cardDeck.begin(), cardDeck.end(), g);
}

// refactored
// sets activeCard to player's choice
void Player::chooseCard() {
    client::InputHandler inputHandler;
    int selectedIndex = inputHandler.chooseCardFromHand(handCards);

    if (selectedIndex != -1) {
        activeCard = handCards.at(selectedIndex);
        std::cout<<"You chose card with ID: " + std::to_string(activeCard)<<std::endl;
    } else {
        std::cout<<"Failed to choose a card."<<std::endl;
    }
}

void Player::playTurn(std::vector<Player*> playerList){ // à mettre dans engine
    Game::time = DAY;
    std::cout << "Current time: " << (Game::time ? "DAY" : "NIGHT") << std::endl;

    engine::ActionProcessor actionProcessor;
    //actionProcessor.performAction(this, );
    //
    //
    //
    //
}

void Player::moveCardToHand () { // engine
    handCards.push_back(cardDeck.at(0));
    cardDeck.erase(cardDeck.begin());
}

void Player::moveCardToDeck() { // engine
    cardDeck.push_back(activeCard);
}

bool Player::checkCombat(std::vector<Player*> playerList){ // à mettre dans engine
    opponentsList.clear();
    for (Player* otherPlayer : playerList) {
        if (otherPlayer != this && otherPlayer->getPosition() == this->getPosition()) {
            opponentsList.push_back(otherPlayer);
        }    
    }
    return !opponentsList.empty();
}

Player* Player::chooseOpponent(){
    engine::CombatManager combatManager;
    return combatManager.chooseOpponent(opponentsList, name);
    // if (opponentsList.empty()) {
    //     std::cout << "You have no opponent, enjoy. " << name << "." << std::endl;
    //     return nullptr;
    // }
    // std::cout << "Choose an opponent in your opponentsList : " << std::endl;

    // for (int i = 0; i < opponentsList.size(); ++i) {
    //     Player* opponent = opponentsList[i];
    //     std::cout << i + 1 << ". " << opponent->getName() 
    //               << " (Position: " << opponent->getPosition() << ")" << std::endl;
    // }
    // int choice = 0;
    // while (true) {
    //     std::cout << "Entrez le numéro de l'adversaire que vous voulez choisir : ";
    //     std::cin >> choice;
    //     if (std::cin.fail() || choice < 1 || choice > static_cast<int>(opponentsList.size())) {
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "Entrée invalide. Veuillez entrer un numéro valide." << std::endl;
    //     } else {
    //         break;
    //     }
    // }
    // return opponentsList[choice - 1];
}

bool Player::chooseTimeDice(int dice1, int dice2){ // à mettre dans client
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

const std::vector <int>& Player::getHandCards() const{
    return handCards;
}

int Player::getActiveCard() const{

}

const std::vector <Player*>& Player::getOpponentsList() const{
    return opponentsList;
}

}