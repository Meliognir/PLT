#include "Player.h"
#include "Game.h"
#include "State.h"
#include "ActionCard.h"
#include "BoatHold.h"
#include "Gold.h"
#include "Food.h"
#include "Canon.h"
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
#define STAR 1000

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
    activeCard = -1;
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

void Player::shuffleDeck(){
    std::random_device rd;
    // Mersenne Twister PRNG init with rd
    std::mt19937 g(rd());
    std::shuffle(cardDeck.begin(), cardDeck.end(), g);
}

// refactored
// sets activeCard to player's choice
/*void Player::chooseCard() {
    client::InputHandler inputHandler;
    int selectedIndex = inputHandler.chooseCardFromHand(handCards);

    if (selectedIndex != -1) {
        activeCard = handCards.at(selectedIndex);
        std::cout<<"You chose card with ID: " + std::to_string(activeCard)<<std::endl;
    } else {
        std::cout<<"Failed to choose a card."<<std::endl;
    }
}*/

/*void Player::playTurn(std::vector<Player*> playerList){ // à mettre dans engine
    Game::time = DAY;
    std::cout << "Current time: " << (Game::time ? "DAY" : "NIGHT") << std::endl;

}*/

void Player::moveCardToHand () {
    if (cardDeck.empty()) {
        std::cerr << "Error: Cannot move card to hand. The card deck is empty." << std::endl;
        return;
    }
    handCards.push_back(cardDeck.at(0));
    cardDeck.erase(cardDeck.begin());
}

void Player::moveCardToDeck() {
    if (activeCard == -1) {
        std::cerr << "Error: No active card to move to the deck." << std::endl;
        return;
    }
    cardDeck.push_back(activeCard);
    activeCard = -1;
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

/*Player* Player::chooseOpponent(){
    engine::CombatManager combatManager;
    return combatManager.chooseOpponent(opponentsList, name);
}*/

void Player::addResourcesToBoatHold(std::string resourceType, int boatholdIndex, int amount, int skipSelection){
    auto& boatHolds = getBoatHolds();
    state::BoatHold *selectedHold;
    if (skipSelection){
        selectedHold = getBoatHolds().at(skipSelection-1);
    }
    else {
        selectedHold = boatHolds[boatholdIndex-1];
    }
    int quantityToRemove = selectedHold->getQuantity();
    selectedHold->removeResource(quantityToRemove);
    if (resourceType == "Food"){
        auto foodResource = make_unique<Food>();
        selectedHold->addResource(std::move(foodResource), amount);
        return;
    }
    if (resourceType == "Gold"){
        auto goldResource = make_unique<Gold>();
        selectedHold->addResource(std::move(goldResource), amount);
        return;
    }
    if (resourceType == "Canon"){
        auto canonResource = make_unique<Canon>();
        selectedHold->addResource(std::move(canonResource), amount);
        return;
    }
    std::cout<< "Something was wrong with this resource, we destroyed it for you" << std::endl;
}

void Player::removeFromBoatHold(int boatholdIndex, int amount){
    auto& boatHolds = getBoatHolds();
    state::BoatHold *selectedHold;
    selectedHold = boatHolds[boatholdIndex-1];
    selectedHold->removeResource(amount);
}

bool Player::chooseTimeDice(int dice1, int dice2)
{ // à mettre dans client
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

int Player::rollCombatDie(){
    const int dieValues[] = {2, 4, 6, 8, 10, STAR};

    const int sides = sizeof(dieValues) / sizeof(dieValues[0]);

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, sides - 1);

    return dieValues[distrib(gen)];
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

int Player::getPath() const
{
    return path;
}

void Player::setPath(int path)
{
    this->path = path;
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
 return activeCard;
}

void Player::setActiveCard(int activeCard){
    this->activeCard=activeCard;
}

const std::vector <Player*>& Player::getOpponentsList() const{
    return opponentsList;
}

int Player::getFirePower() const{
    return firePower;
}

void Player::setFirePower(int firePower)
{
    this->firePower=firePower;
}

ai::AI *Player::get_AI()
{
    // TODO: insert return statement here
    return AIptr;
}

bool Player::getBankrupt() const
{
    return bankrupt;
}

void Player::setBankrupt(bool bankrupt)
{
    this->bankrupt = bankrupt;
}



}