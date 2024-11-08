#include "ActionCard.h"
#include "Player.h"

namespace state {

    ActionCard::ActionCard(int cardID, Player *owner) : cardOwner(owner)
    {
        //create the correct action card according to its cardID
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