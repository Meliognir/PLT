//
// Created by trias on 18/12/24.
//

#include "AI.h"
#include "DeepAI.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <string>
#include <stdlib.h>
#include <vector>

#define DEEP_PLACE_HOLDER 1

ai::DeepAI::DeepAI(state::Game* game): AI(game) {

}

//when demande input : rand() response




std::string ai::DeepAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : Débutant";
    playerName= "Débutant";
    return playerName;
}


size_t ai::DeepAI::selectUserBoatHold(size_t boatHoldCount, std::string resTypeToPay, int currentPlayerIndex){
    size_t index = 0;
    while (true) {
        std::cout << "You have " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : ";
        index=DEEP_PLACE_HOLDER;
        if (index < 1 || index > boatHoldCount) {
            std::cout << "Invalid index. Please enter a number between 1 and " << boatHoldCount << ".\n";
            continue;
        }
        return index;
    }
}



int ai::DeepAI::chooseCardFromHand(const std::vector<int>& handCards) {
    std::cout<<"Your 3 handCards:"<<std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice = 0;
    std::cout<<"Choose a card, enter an index between 1 and 3:"<<std::endl;
    choice=DEEP_PLACE_HOLDER;

    return choice;
}

bool ai::DeepAI::chooseTimeDice(int die1, int die2){
    std::string input;
    while (true) {
        std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
                  << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
        input=DEEP_PLACE_HOLDER;
        if (input == "1" || input == "2") {
            break;
        }
        std::cout << "Entrée invalide. Veuillez entrer '1' ou '2'.\n";
    }
    return input == "1";
}

int ai::DeepAI::chooseCanonNb(int totalNb){
    if (totalNb <= 0) {
        std::cout << "You don't have any available canons." << std::endl;
        return 0;
    }
    int chosenNb = 0;

    std::cout << "You have " << totalNb << " available canons. How many do you want to use ? ";
    chosenNb=DEEP_PLACE_HOLDER;
    return chosenNb;
}

int ai::DeepAI::chooseOpponent(size_t listSize)
{
    return DEEP_PLACE_HOLDER;
}

ai::DeepAI::~DeepAI()
{
}
