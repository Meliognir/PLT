#include "DiceManager.h"
#include <cstdlib>
#include <random>
#define STAR 1000

std::array<int, 2> engine::DiceManager::rollDice(){
    return {rand() % 6 + 1, rand() % 6 + 1};
}

std::array<int, 2> engine::DiceManager::assignDayAndNightDice(int die1, int die2, bool dayFirst){
    return dayFirst ? std::array<int, 2>{die1, die2} : std::array<int, 2>{die2, die1};
}

int engine::DiceManager::rollCombatDie(){
    const int dieValues[] = {2, 4, 6, 8, 10, STAR};

    const int sides = sizeof(dieValues) / sizeof(dieValues[0]);

    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, sides - 1);

    return dieValues[distrib(gen)];
}
