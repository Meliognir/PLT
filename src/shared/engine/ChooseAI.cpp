#include "ChooseAI.h"
#include "../ai.h"

engine::ChooseAI::ChooseAI(int levelAI, int playerIndex) : levelAI(levelAI), playerIndex(playerIndex)
{
}

void const engine::ChooseAI::launchCommand(state::Game *GamePtr)
{
    state::Player *targetedPlayer = GamePtr->getPlayerList().at(playerIndex);
    switch (levelAI)
    {
    case 0:
        break;
    case 1:
        //ai::AI *aiInstance = new ai::RandomAI();
        targetedPlayer->set_AI(new ai::RandomAI());
        break;
    case 2:
        //ai::AI *aiInstance = new ai::HeuristicAI();
        targetedPlayer->set_AI(new ai::HeuristicAI(GamePtr));
        break;
    case 3:
        //ai::AI *aiInstance = new ai::DeepAI();
        targetedPlayer->set_AI(new ai::DeepAI(GamePtr));
        break;
    
    default:
        break;
    }
}

engine::ChooseAI::~ChooseAI()
{
}
