//
// Created by trias on 18/12/24.
//

#include "AI.h"
#include "RandomAI.h"
#include <iostream>
#include <cstdlib>


int getRandomInput(int min, int max) {
    return min + std::rand() % ((max - min) + 1);
}

ai::RandomAI::RandomAI() {}



std::string ai::RandomAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : Débutant";
    playerName= "Débutant";
    return playerName;
}


size_t ai::RandomAI::selectUserBoatHold(size_t boatHoldCount){
    size_t index = 0;
    while (true) {
        std::cout << "You have " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : ";
        index=getRandomInput(0,5);
        if (index < 1 || index > boatHoldCount) {
            std::cout << "Invalid index. Please enter a number between 1 and " << boatHoldCount << ".\n";
            continue;
        }
        return index;
    }
}

bool ai::RandomAI::confirmBoatHoldReplace(){
    std::string input;
    while (true) {
        std::cout << "This boathold contains other resources. Do you want to replace them ? (y/n) : ";
        input=="y";

        if (input == "y" || input == "n") {
            return input == "y";
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    }
}

int ai::RandomAI::chooseCardFromHand(const std::vector<int>& handCards) {
    std::cout<<"Your 3 handCards:"<<std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice = 0;
    std::cout<<"Choose a card, enter an index between 1 and 3:"<<std::endl;
    choice=getRandomInput(1,3);

    return choice;
}

bool ai::RandomAI::chooseTimeDice(int die1, int die2){
    std::string input;
    while (true) {
        std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
                  << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
        input=getRandomInput(1,2);
        if (input == "1" || input == "2") {
            break;
        }
        std::cout << "Entrée invalide. Veuillez entrer '1' ou '2'.\n";
    }
    return input == "1";
}

int ai::RandomAI::chooseCanonNb(int totalNb){
    if (totalNb <= 0) {
        std::cout << "You don't have any available canons." << std::endl;
        return 0;
    }
    int chosenNb = 0;

    std::cout << "You have " << totalNb << " available canons. How many do you want to use ? ";
    chosenNb=getRandomInput(0,totalNb);
    return chosenNb;
}

ai::RandomAI::~RandomAI()
{
}
