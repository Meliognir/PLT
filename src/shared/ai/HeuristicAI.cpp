//
// Created by trias on 18/12/24.
//

#include "AI.h"
#include "HeuristicAI.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <state/BoatHold.h>
#include <state/Player.h>

#define HEURISTIC_PLACE_HOLDER 1


ai::HeuristicAI::HeuristicAI(state::Game* game): AI(game) {


}


std::string ai::HeuristicAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : Moyen";
    playerName= "Moyen";
    return playerName;
}


size_t ai::HeuristicAI::selectUserBoatHold(size_t boatHoldCount) {
    size_t index = 0;

    bool found = false;

    // Vérifier s'il existe un BoatHold vide
    while (!found) {
        int i = 0;
        std::cout << "You have " << boatHoldCount << " BoatHolds. Picking the first empty one..." << std::endl;

        for (state::BoatHold* boathold : controlledPlayer->getBoatHolds()) {
            if (boathold->isEmpty()) {
                index = i;
                found = true;
                break;
            }
            i++;
        }

        if (!found) {
            std::cout << "All boat holds are occupied. No empty boat hold found." << std::endl;

            // Enlever les ressources de type CANON si aucun BoatHold n'est vide
            bool removedCanon = false;
            for (state::BoatHold* boathold : controlledPlayer->getBoatHolds()) {
                if (boathold->hasResourceType("CANON")) {
                    boathold->removeResource(boathold->getQuantity());
                    std::cout << "Removed 'CANON' from BoatHold." << std::endl;
                    removedCanon = true;
                    break;
                }
            }

            if (!removedCanon) {
                // Trouver le BoatHold avec le moins de ressources et enlever ces ressources
                state::BoatHold* boatHoldWithLeastResources = nullptr;
                size_t leastResourceCount = SIZE_MAX;

                for (state::BoatHold* boathold : controlledPlayer->getBoatHolds()) {
                    if (boathold->getQuantity() < leastResourceCount) {
                        leastResourceCount = boathold->getQuantity();
                        boatHoldWithLeastResources = boathold;
                    }
                }

                if (boatHoldWithLeastResources) {
                    // Si la ressource est différente, enlevez là où il y en a le moins
                    int quantity = boatHoldWithLeastResources->getQuantity();
                    if (quantity > 0) {
                        boatHoldWithLeastResources->removeResource(boatHoldWithLeastResources->getQuantity());
                        std::cout << "Removed resources from BoatHold with least resources." << std::endl;
                    }
                }
            }
        }
    }

    // S'assurer que l'index est dans une plage valide si trouvé
    if (index < 0 || index >= boatHoldCount) {
        std::cout << "Invalid index. Returning default placeholder index." << std::endl;
        index = HEURISTIC_PLACE_HOLDER;
    }

    return index;
}



bool ai::HeuristicAI::confirmBoatHoldReplace(){
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

int ai::HeuristicAI::chooseCardFromHand(const std::vector<int>& handCards) {
    std::cout<<"Your 3 handCards:"<<std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice = 0;
    std::cout<<"Choose a card, enter an index between 1 and 3:"<<std::endl;
    choice=HEURISTIC_PLACE_HOLDER;

    return choice;
}

bool ai::HeuristicAI::chooseTimeDice(int die1, int die2){
    int input;
    std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
              << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;

    return input == 1;
}

int ai::HeuristicAI::chooseCanonNb(int totalNb){
    if (totalNb <= 0) {
        std::cout << "You don't have any available canons." << std::endl;
        return 0;
    }
    int chosenNb = 0;

    std::cout << "You have " << totalNb << " available canons. How many do you want to use ? ";
    chosenNb=HEURISTIC_PLACE_HOLDER;
    return chosenNb;
}

int ai::HeuristicAI::chooseOpponent(size_t listSize)
{
    return 0;
}

ai::HeuristicAI::~HeuristicAI()
{
}
