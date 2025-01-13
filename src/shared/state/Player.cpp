#include "Player.h"
#include "Game.h"
#include "State.h"
#include "ActionCard.h"
#include "BoatHold.h"
#include "Gold.h"
#include "Food.h"
#include "Canon.h"
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
    //ajout de la valeur activeCard en fin de cardDeck
    cardDeck.push_back(activeCard);
    //effaçage de activeCard dans handCards
    auto it = std::find(handCards.begin(), handCards.end(), activeCard);
    if (it != handCards.end()) {
        activeCardId = std::distance(handCards.begin(), it);
    } else {
        std::cerr << "Error: activeCard not found in handCards." << std::endl;
        activeCardId = -1;
    }
    handCards.erase(handCards.begin() + activeCardId);
    this->usedCardNb++;
    this->activeCard = -1;
    //8 activeCards were used
    if(this->usedCardNb == 8){
        this->shuffleDeck();
        this->usedCardNb = 0;
    }
}

void Player::moveWithDirection (int distance, int direction){ // ajouter taille de map parametre
    int currentPos = this->getPosition();
    signed int nextPos = currentPos + distance*direction;
    std::cout << "nextPos: " << nextPos << "\r\n" << std::endl;
    //if(nextPos >= Map::getSize()){this->setPosition(Map::getSize());}
    this->setPosition(nextPos);
}

void Player::addResourcesToBoatHold(std::string resourceType, int boatholdIndex, int amount){
    auto& boatHolds = this->getBoatHolds();
    state::BoatHold *selectedHold;
    selectedHold = boatHolds.at(boatholdIndex);
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
    auto& boatHolds = this->getBoatHolds();
    state::BoatHold *selectedHold;
    selectedHold = boatHolds.at(boatholdIndex);
    selectedHold->removeResource(amount);
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

void Player::setOpponentsList(const std::vector<Player *> &opponentsList)
{
    this->opponentsList = opponentsList;
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

void Player::set_AI(ai::AI *aiInstance)
{
    // TODO: insert return statement here
    this->AIptr = aiInstance;
}

bool Player::getBankrupt() const
{
    return bankrupt;
}

void Player::setBankrupt(bool bankrupt)
{
    this->bankrupt = bankrupt;
}

int Player::getChosenBoatholdIndex() const
{
    return chosenBoatholdIndex;
}

void Player::setChosenBoatholdIndex(int chosenBoatholdIndex)
{
    this->chosenBoatholdIndex = chosenBoatholdIndex;
}
bool Player::getMustFight() const
{
    return this->mustFight;
}
void Player::setMustFight(bool mustFight)
{
    this->mustFight = mustFight;
}
bool Player::getHasToPay() const
{
    return this->hasToPay;
}
void Player::setHasToPay(bool hasToPay)
{
    this->hasToPay = hasToPay;
}
const std::string &Player::getResTypeToPay() const
{
    return this->resTypeToPay;
}
void Player::setResTypeToPay(const std::string &resTypeToPay)
{
    this->resTypeToPay = resTypeToPay;
}
int Player::getAmountToPay() const
{
    return this->amountToPay;
}
void Player::setAmountToPay(int amountToPay)
{
    this->amountToPay = amountToPay;
}
bool Player::getHasMoved() const
{
    return this->hasMoved;
}
void Player::setHasMoved(bool hasMoved)
{
    this->hasMoved = hasMoved;
}
}