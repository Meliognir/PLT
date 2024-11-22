#include "DiceManager.h"
#include <cstdlib>

std::pair<int, int> engine::DiceManager::rollDice(){
    return {rand() % 6 + 1, rand() % 6 + 1};
}

std::pair<int, int> engine::DiceManager::assignDayAndNightDice(int die1, int die2, bool dayFirst){
    return dayFirst ? std::make_pair(die1, die2) : std::make_pair(die2, die1);
}
