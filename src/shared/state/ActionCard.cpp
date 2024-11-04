#include "ActionCard.h"

namespace state {

    ActionCard::ActionCard(int cardID, Player *owner) : cardOwner(owner)
    {
        //create the correct action card according to its cardID
    }

    void ActionCard::move()
    {
        //cardOwner->position = 2;

    }

    ActionCard::~ActionCard()
    {
    }

}