#include "RollDice.h"
#include "state.h"

namespace engine{
    RollDice::RollDice(int dieType, int playerIndex) : dieType(dieType), playerIndex(playerIndex){
    }

    void const RollDice::launchCommand(state::Game * GamePtr){
        if(!dieType){
            //Normal Die
            GamePtr->rollDice();
        }
        else{
            //Combat Die
            state::Player * player;
            player = GamePtr->getPlayerList()[playerIndex];
            player->rollCombatDie();
        }
    }
}