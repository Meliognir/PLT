#include "ActionCard.h"
#include "Player.h"
#include "Game.h"

#include "Canon.h"
#include "Gold.h"
#include "Food.h"

#include <utility>

#define DAY true
#define NIGHT false

namespace state {

    ActionCard::ActionCard(uint8_t dayAction, uint8_t nightAction) : cardOwner(nullptr), dayAction(dayAction), nightAction(nightAction) {
    }

    ActionCard::~ActionCard(){
    }

    ActionCard::ActionCard(int cardID, Player *owner) : cardOwner(owner){
        //create a copy of the original action card, based on its cardID
        ActionCard *original = Game::collectionOfCards[cardID];
        dayAction = original->dayAction;
        nightAction = original->nightAction;       
    }

    void ActionCard::move(){
        int current_pos = cardOwner->getPosition();
        cardOwner->setPosition(current_pos+1);
    }

    void ActionCard::addCanons() {
        if (Game::time == DAY){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Canon>(), Game::dayDice);
        }
        if (Game::time == NIGHT){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Canon>(), Game::nightDice);
        }
    }

    void ActionCard::addFood() {
        if (Game::time == DAY){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Food>(), Game::dayDice);
        }
        if (Game::time == NIGHT){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Food>(), Game::nightDice);
        }
    }

    void ActionCard::addGold() {
        if (Game::time == DAY){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Gold>(), Game::dayDice);
        }
        if (Game::time == NIGHT){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Gold>(), Game::nightDice);
        }
    }

    const uint8_t& ActionCard::getDayAction() const {
        return dayAction;
    }

    const uint8_t& ActionCard::getNightAction() const {
        return nightAction;
    }

}