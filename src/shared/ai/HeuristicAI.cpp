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

std::vector <int> ai::HeuristicAI::takenNamesIndex = {};

std::string getHeuristicName(std::vector <int> *takenNamesIndex){
    std::vector <std::string> nameList = {"Master Yoda", "Master Oogway", "Master Roshi", "Professor Chen", "Professor X", "Professor Tournesol", "Professor Sadok", "Professor Tauvel", "Professor Bares", "Professor Nguyen", "Professor Layton"};
    int select;
    bool validName = false;
    while (!validName){
        validName = true;
        select = rand()%nameList.size();
        for (int takenIndex : *takenNamesIndex){
            validName = validName && (select != takenIndex);
        }
    }
    (*takenNamesIndex).push_back(select);
    return nameList.at(select);
}

ai::HeuristicAI::HeuristicAI(state::Game* game): AI(game) {
}


std::string ai::HeuristicAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : ";
    playerName= getHeuristicName(&takenNamesIndex);
    return playerName;
}


void removeOneBoatHold(size_t boatHoldCount, std::vector<state::BoatHold *> controlledBoatHold, std::string resToAdd){
    std::cout << "AI : All boat holds are occupied. No empty boat hold found." << std::endl;

    // Enlever les ressources de type "Canon" par défaut
    bool removedCanon = false;
    for (state::BoatHold* bh : controlledBoatHold) {
        if (bh->hasResourceType("Canon") && bh->getResourceType() != resToAdd) {
            bh->removeResource(bh->getQuantity()); // donner à l'engine faire ceci
            std::cout << "AI : Removed 'Canon' from BoatHold." << std::endl;
            removedCanon = true;
            break;
        }
    }   

    // Cas où il n'y a pas de ressources de type "Canon"
    if (!removedCanon) {
        std::cout << "AI : has no 'Canon' to remove from BoatHold." << std::endl;
        // Trouver le BoatHold avec le moins de ressources et enlever ses ressources
        // Cela peut enlever des ressources Gold ou Food
        state::BoatHold* boatHoldWithLeastResources = nullptr;
        size_t leastResourceAmount = SIZE_MAX;

        for (state::BoatHold* bh : controlledBoatHold) {
            // Si plusieurs min trouvés, le premier trouvé est return
            if (bh->getQuantity() < leastResourceAmount && bh->getResourceType() != resToAdd) {
                leastResourceAmount = bh->getQuantity();
                boatHoldWithLeastResources = bh;
            }
        }

        if (boatHoldWithLeastResources) {
            // condition vraie normalement
            if (leastResourceAmount > 0) {
                boatHoldWithLeastResources->removeResource(leastResourceAmount);
                std::cout << "AI : Removed resources (Gold or Food) from BoatHold with the least resources." << std::endl;
            }
        }
        else{
            std::cout << "AI : Error failed to find BoatHold with the least resources." << std::endl;
        }
    }
}


// -changer client.cpp car il y a trop de répétition de code, cela devient difficile de gérer tous les cas de selectUserBoatHold
// -changer de nom currentPlayerIndex en playerIndex juste pour spécifier le joueur cible, si non init ( = -1 ) alors le joueur est l'IA
// -client.cpp devrait tout le temps appeler avec les 3 inputs, ce n'est pas le cas
// -l'IA devrait passer par des commandes dans engine pour modifier ses Boatholds
size_t ai::HeuristicAI::selectUserBoatHold(size_t boatHoldCount, std::string resType, int currentPlayerIndex, bool hasToPay) {
    size_t index = 0;
    std::vector<state::BoatHold *> controlledBoatHold = controlledPlayer->getBoatHolds();
    int stateId = gameView->state->getStateId();

    // Rien à payer
    if (!hasToPay){
        bool found = false;

        // Pas de AttackingState, DefendingState, StealState
        if(stateId != 6 && stateId !=7 && stateId != 8){

            // Vérifier si 1 de mes BoatHolds est vide pour recevoir une Ressource par carte ou par vol
            // Vider 1 Boathold si aucun vide
            while (!found) {
                int i = 0;
                std::cout << "You have " << boatHoldCount << " BoatHolds. Picking the first empty one..." << std::endl;

                for (state::BoatHold* bh : controlledBoatHold) {
                    if (bh->isEmpty()) {
                        index = i;
                        found = true;
                        break;
                    }
                    i++;
                }

                // Si aucun Boathold n'est vide
                if (!found) {
                    removeOneBoatHold(boatHoldCount, controlledBoatHold, resType);
                }
            }
        }
        // StealState : Voler un Boathold avec des food ou du gold de mon adversaire si je gagne un duel
        if(stateId == 8){

            // Voler loser player donné par client.cpp
            if(currentPlayerIndex != -1){
                std::cout << "AI : Stealing loser's Resources." << std::endl;

                state::Player* loser = gameView->getPlayerList().at(currentPlayerIndex);
                std::vector<state::BoatHold *> boatholdsToSteal = loser->getBoatHolds();

                // Calculer la Ressource avec le plus de quantité de Gold ou Food
                int i = 0;
                size_t maxAmount = 0;
                for(state::BoatHold* bh : boatholdsToSteal){
                    if (bh->hasResourceType("Gold") || bh->hasResourceType("Food")){
                        if(bh->getQuantity() > maxAmount){
                            maxAmount = bh->getQuantity();
                            index = i;
                        }
                    }
                    i++;
                }
                std::cout << "AI : Found Food or Gold Resources in opponent's Boathold." << std::endl;
            }
            // Recevoir une Ressource volée gold ou food
            // Le cas isFull de cette Ressource est géré par client.cpp
            else{
                while (!found) {
                    
                    int i = 0;
                    for (state::BoatHold* bh : controlledBoatHold) {
                        if (bh->isEmpty()) {
                            index = i;
                            found = true;
                            break;
                        }
                        i++;
                    }

                    if (!found) {
                        removeOneBoatHold(boatHoldCount, controlledBoatHold, resType);
                    }
                    else{
                        return index;
                    }
                }
            }
        }
    }

    // Doit payer, Bankrupt est géré par client.cpp donc normalement l'AI peut payer
    if (hasToPay && stateId != 8) {
        int i = 0;
        for (state::BoatHold* bh : controlledBoatHold) {
            if (bh->hasResourceType(resType)) {
                index = i;
                std::cout << "AI : Found " << resType <<  "in BoatHold " << index <<"."<< std::endl;
                break;
            }
            i++;
        }
    }

    // index = i from 0 to boatHoldCount-1
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

    std::cout << "AI : Chosen card index: " << choice << std::endl;
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
            std::cout << "AI chose " <<die1 <<" as the day number."<< std::endl;
            return die1;
        } else if (die1<=die2 && (controlledPlayer->getHandCards().at(choice)==1 ||controlledPlayer->getHandCards().at(choice)==3 ||controlledPlayer->getHandCards().at(choice)==0 ||controlledPlayer->getHandCards().at(choice)==7)) {
            std::cout << "AI chose " <<die2 <<" as the day number and it's a good choice."<< std::endl;
            return die2;
        } else if (die1>=die2 && (controlledPlayer->getHandCards().at(choice)==2 ||controlledPlayer->getHandCards().at(choice)==4 ||controlledPlayer->getHandCards().at(choice)==8)) {
            std::cout << "AI chose " <<die2 <<" as the day number and it's a good choice ."<< std::endl;
            return die2;
        }else if (die1<=die2 && (controlledPlayer->getHandCards().at(choice)==2 ||controlledPlayer->getHandCards().at(choice)==4 ||controlledPlayer->getHandCards().at(choice)==8)) {
            std::cout << "AI chose " <<die1 <<" as the day number."<< std::endl;
            return die1;
        }else {
            std::cout << "AI chose " <<die1 <<" as the day number."<< std::endl;
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
