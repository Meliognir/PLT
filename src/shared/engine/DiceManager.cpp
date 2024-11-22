#include "DiceManager.h"
#include <cstdlib>

std::array<int, 2> engine::DiceManager::rollDice(){
    return {rand() % 6 + 1, rand() % 6 + 1};
}

std::array<int, 2> engine::DiceManager::assignDayAndNightDice(int die1, int die2, bool dayFirst){
    return dayFirst ? std::array<int, 2>{die1, die2} : std::array<int, 2>{die2, die1};
}
