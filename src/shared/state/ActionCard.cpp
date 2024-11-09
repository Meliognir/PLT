#include "ActionCard.h"
#include "Player.h"
#include "Game.h"

namespace state {

    ActionCard::ActionCard(const std::string& dayAction, const std::string& nightAction) : cardOwner(nullptr), dayAction(dayAction), nightAction(nightAction) {
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
        
    }

    void ActionCard::addFood() {
    
    }

    void ActionCard::addGold() {
    
    }

    const std::string& ActionCard::getDayAction() const {
        return dayAction;
    }

    void ActionCard::setDayAction(const std::string& dayAction) {
        this->dayAction = dayAction;
    }

    const std::string& ActionCard::getNightAction() const {
        return nightAction;
    }

    void ActionCard::setNightAction(const std::string& nightAction) {
        this->nightAction = nightAction;
    }

}