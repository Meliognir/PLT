#include "ChooseCard.h"
#include "../shared/state/Player.h"

engine::ChooseCard::ChooseCard(state::Player* activePlayer, int card) : activePlayer(activePlayer), card(card){}

void const engine::ChooseCard::launchCommand(state::Game *GamePtr){
    activePlayer->setActiveCard(card);
    return;
}

engine::ChooseCard::~ChooseCard(){}