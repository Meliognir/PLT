#include "ChooseOpponent.h"

engine::ChooseOpponent::ChooseOpponent(int playerAttacking, int playerDefending) : playerAttackingIndex(playerAttacking), defendingPlayerIndex(playerDefending){}

void const engine::ChooseOpponent::launchCommand(state::Game *GamePtr){
    state::Player* attackingplayer = GamePtr->getPlayerList()[playerAttackingIndex];
    state::Player* defendingplayer = GamePtr->getPlayerList()[defendingPlayerIndex];
    GamePtr->setAttackingPlayer(attackingplayer);
    GamePtr->setDefendingPlayer(defendingplayer);
    return;
}

engine::ChooseOpponent::~ChooseOpponent(){}