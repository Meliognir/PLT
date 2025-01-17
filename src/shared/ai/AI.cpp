#include "AI.h"

#include <state/Game.h>

ai::AI::AI(state::Game* game)
{
    gameView=game;
    controlledPlayer=gameView->getActivePlayer();
}

std::string ai::AI::getPlayerName(int playerIndex)
{
    return std::string();
}

size_t ai::AI::selectUserBoatHold(size_t boatHoldCount, std::string resType, int currentPlayerIndex, bool hasToPay)
{
    return size_t();
}


int ai::AI::chooseCardFromHand(const std::vector<int> &handCards)
{
    return 0;
}

bool ai::AI::chooseTimeDice(int die1, int die2)
{
    return false;
}

int ai::AI::chooseCanonNb(int totalNb)
{
    return 0;
}

int ai::AI::chooseOpponent(size_t listSize)
{
    return 0;
}

ai::AI::~AI()
{
}
