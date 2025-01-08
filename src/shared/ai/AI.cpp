#include "AI.h"

ai::AI::AI()
{
}

std::string ai::AI::getPlayerName(int playerIndex)
{
    return std::string();
}

size_t ai::AI::selectUserBoatHold(size_t boatHoldCount)
{
    return size_t();
}

bool ai::AI::confirmBoatHoldReplace()
{
    return false;
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
