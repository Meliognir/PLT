#include "ChooseCard.h"
#include "../shared/state/Player.h"

engine::ChooseCard::ChooseCard(state::Player* playingPlayer, int card) : playingPlayer(playingPlayer), card(card){}

void const engine::ChooseCard::launchCommand(state::Game *GamePtr){
    playingPlayer->setActiveCard(card);
    return;
}

engine::ChooseCard::~ChooseCard(){}