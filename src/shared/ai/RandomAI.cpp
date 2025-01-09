
#include "AI.h"
#include "RandomAI.h"
#include <state/BoatHold.h>
#include <state/Game.h>
#include <state/Player.h>

#include <iostream>
#include <cstdlib>


int getRandomInput(int min, int max) {
    return min + std::rand() % ((max - min) + 1);
}

ai::RandomAI::RandomAI(state::Game* game): AI(game) {}



std::string ai::RandomAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : Débutant" << std::endl;
    playerName= "Débutant";
    return playerName;
}


size_t ai::RandomAI::selectUserBoatHold(size_t boatHoldCount, std::string resTypeToPay, int currentPlayerIndex){
    size_t index = 0;
    bool invalidInput = true;
    state::Player* currentPlayer = gameView->getPlayerList().at(currentPlayerIndex);
    std::vector <state::BoatHold *> currentPlayerBoatHolds = currentPlayer->getBoatHolds();
    std::cout << "You have " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : ";
    while (invalidInput){
        index=getRandomInput(1, boatHoldCount);
        if (resTypeToPay == ""){
            invalidInput = false;
        }
        else{
            if (resTypeToPay == currentPlayerBoatHolds.at(index-1)->getResourceType()){
                invalidInput = false;
            }
        }
    }
    std::cout << currentPlayer->getName() << " selected the boat hold " << index << "." << std::endl;
    return index-1;

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
    choice=getRandomInput(0,2);

    return choice;
}

bool ai::RandomAI::chooseTimeDice(int die1, int die2){
    int input;
    std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
              << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
    input=getRandomInput(0,1);
    return input == 1;
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

int ai::RandomAI::chooseOpponent(size_t listSize)
{
    int chosenOpponent = getRandomInput(1, listSize);
    return chosenOpponent-1;
}

ai::RandomAI::~RandomAI()
{
}
