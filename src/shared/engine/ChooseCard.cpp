#include "ChooseCard.h"

engine::ChooseCard::ChooseCard(int player, int card) : playerIndex(player), card(card){}

void const engine::ChooseCard::launchCommand(state::Game *GamePtr){
    state::Player* player = GamePtr->getPlayerList()[playerIndex];
    player->setActiveCard(card);
    return;
}

engine::ChooseCard::~ChooseCard(){}