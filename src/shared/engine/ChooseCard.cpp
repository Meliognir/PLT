#include "ChooseCard.h"

void const engine::ChooseCard::launchCommand(state::Game *GamePtr){
    state::Player* player = GamePtr->getPlayerList()[playerIndex];
    player->setActiveCard(card);
    return;
}

engine::ChooseCard::ChooseCard(int player, int card) : playerIndex(player), card(card){
}