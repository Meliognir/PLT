#include "ActionCard.h"
#include "Player.h"
#include "Game.h"

namespace state {

    ActionCard::ActionCard(int dayAction, int nightAction) : cardOwner(nullptr), dayAction(dayAction), nightAction(nightAction) 
    {        
    }

    ActionCard::ActionCard(int cardID, Player *owner) : cardOwner(owner)
    {
        //create a copy of the original action card, based on its cardID
        ActionCard *original = Game::collectionOfCards[cardID];

        dayAction = original->dayAction;
        nightAction = original->nightAction;       
        
    }


    void ActionCard::move()
    {
        int current_pos = cardOwner->getPosition();
        cardOwner->setPosition(current_pos+1);

    }

    ActionCard::~ActionCard()
    {
    }

}