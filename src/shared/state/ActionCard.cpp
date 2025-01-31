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
        ActionCard *original = Game::collectionOfCards.at(cardID);
        dayAction = original->dayAction;
        nightAction = original->nightAction;       
    }

    /*void ActionCard::move(int direction){
        int current_pos = cardOwner->getPosition();
        if (Game::time == DAY){
            cardOwner->setPosition(current_pos+Game::dayDie);
        }
        if (Game::time == NIGHT){
            cardOwner->setPosition(current_pos+Game::nightDie);
        }
    }*/

    void ActionCard::addCanons() {/*
        if (Game::time == DAY){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Canon>(), Game::dayDie);
        }
        if (Game::time == NIGHT){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Canon>(), Game::nightDie);
        }*/
    }

    void ActionCard::addFood() {/*
        if (Game::time == DAY){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Food>(), Game::dayDie);
        }
        if (Game::time == NIGHT){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Food>(), Game::nightDie);
        }*/
    }

    void ActionCard::addGold() {/*
        if (Game::time == DAY){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Gold>(), Game::dayDie);
        }
        if (Game::time == NIGHT){
            cardOwner->addResourcesToBoatHold(std::unique_ptr<Gold>(), Game::nightDie);
        }*/
    }

    const uint8_t& ActionCard::getDayAction() const {
        return dayAction;
    }

    const uint8_t& ActionCard::getNightAction() const {
        return nightAction;
    }

}