//
// Created by trias on 18/12/24.
//

#include "AI.h"
#include "HeuristicAI.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <state/BoatHold.h>
#include <state/Game.h>
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


size_t ai::HeuristicAI::selectUserBoatHold(size_t boatHoldCount, std::string resTypeToPay, int currentPlayerIndex) {
    size_t index = 0;


    if (resTypeToPay == ""){
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

    }

    // S'assurer que l'index est dans une plage valide si trouvé
    if (index < 0 || index >= boatHoldCount) {/*
        std::cout << "Invalid index. Returning a valid random input." << std::endl;

        index = 0;
        bool invalidInput = true;

        if (currentPlayerIndex == -1){
            currentPlayerIndex = gameView->getActivePlayerIndex();
        }

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
        std::cout << currentPlayer->getName() << " selected the boat hold " << index << "." << std::endl;*/
        return index-1;
        
        }

    return index;
}


int ai::HeuristicAI::chooseCardFromHand(const std::vector<int>& handCards) {
    std::cout << "Your 3 handCards:" << std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice;
    bool foundNonCanonCard = false;


    for (size_t i = 0; i < handCards.size(); ++i) {
        if (handCards[i] != 4 && handCards[i] != 5 && handCards[i] != 9 && handCards[i] != 10) {
            choice = i ; // Adjust for 1-based index
            foundNonCanonCard = true;
        }
        // If no cards without "CANON" are found, default to the first card
        if (!foundNonCanonCard) {
            choice = 1; // Default to the first card
        }
    }

    std::cout << "Chosen card index: " << choice << std::endl;
    return choice;
}




bool ai::HeuristicAI::chooseTimeDice(int die1, int die2) {
    std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
              << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
    int choice;
    bool foundNonCanonCard = false;


    for (size_t i = 0; i < controlledPlayer->getHandCards().size(); ++i) {
        if (controlledPlayer->getHandCards().at(i) != 4 && controlledPlayer->getHandCards().at(i) != 5 && controlledPlayer->getHandCards().at(i) != 9 && controlledPlayer->getHandCards().at(i) != 10) {
            choice = i ; // Adjust for 1-based index
            foundNonCanonCard = true;
        }
        // If no cards without "CANON" are found, default to the first card
        if (!foundNonCanonCard) {
            choice = 1; // Default to the first card
        }
    }


        if (die1>=die2 && (controlledPlayer->getHandCards().at(choice)==1 ||controlledPlayer->getHandCards().at(choice)==3 ||controlledPlayer->getHandCards().at(choice)==0 ||controlledPlayer->getHandCards().at(choice)==7)) {
            std::cout << "You choosed " <<die1 <<" as the day number."<< std::endl;
            return die1;
        } else if (die1<=die2 && (controlledPlayer->getHandCards().at(choice)==1 ||controlledPlayer->getHandCards().at(choice)==3 ||controlledPlayer->getHandCards().at(choice)==0 ||controlledPlayer->getHandCards().at(choice)==7)) {
            std::cout << "You choosed " <<die2 <<" as the day number and it's a good choice."<< std::endl;
            return die2;
        } else if (die1>=die2 && (controlledPlayer->getHandCards().at(choice)==2 ||controlledPlayer->getHandCards().at(choice)==4 ||controlledPlayer->getHandCards().at(choice)==8)) {
            std::cout << "You choosed " <<die2 <<" as the day number and it's a good choice ."<< std::endl;
            return die2;
        }else if (die1<=die2 && (controlledPlayer->getHandCards().at(choice)==2 ||controlledPlayer->getHandCards().at(choice)==4 ||controlledPlayer->getHandCards().at(choice)==8)) {
            std::cout << "You choosed " <<die1 <<" as the day number."<< std::endl;
            return die1;
        }else {
            std::cout << "You choosed " <<die1 <<" as the day number."<< std::endl;
            return die1;
        }
}



int ai::HeuristicAI::chooseCanonNb(int totalNb){
    return totalNb;
}

int ai::HeuristicAI::chooseOpponent(size_t listSize) {
    int bestOpponentIndex = 0;
    double highestScore = -std::numeric_limits<double>::infinity();

    for (size_t opponentIndex = 0; opponentIndex < listSize; ++opponentIndex) {
        double score = 0.0;

        state::Player* opponent = controlledPlayer->getOpponentsList().at(opponentIndex);

        if (opponent->getPlayerId()!=controlledPlayer->getPlayerId()) {

            for (state::BoatHold* boathold : opponent->getBoatHolds()) {
                if (boathold->hasResourceType("CANON")) {
                    score -= 0.5 * boathold->getQuantity();
                }
                if (boathold->hasResourceType("FOOD") && boathold->getQuantity() > 2) {
                    score += 1;
                }
                if (boathold->hasResourceType("GOLD") && boathold->getQuantity() > 2) {
                    score += 1;
                }
            }

            if (score > highestScore) {
                highestScore = score;
                bestOpponentIndex = opponentIndex;
            }
        }
    }

    return bestOpponentIndex;
}


ai::HeuristicAI::~HeuristicAI()
{
}
