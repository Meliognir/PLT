//
// Created by trias on 18/12/24.
//

#include "AI.h"
#include "DeepAI.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <vector>
#include <state/BoatHold.h>
#include <state/Game.h>
#include <state/Player.h>

#define DEEP_PLACE_HOLDER 1

std::vector <int> ai::DeepAI::takenNamesIndex = {};

std::string getDeepName(std::vector <int> *takenNamesIndex){
    std::vector <std::string> nameList = {"Doctor Who", "Doctor Chopper", "Doctor Strange", "Doctor Frankenstein", "Doctor Watson", "Doctor House"};
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


ai::DeepAI::DeepAI(state::Game* game): AI(game) {

}

//when demande input : rand() response

//get player density around me
int getPlayerDensity(int nbPlayerAround, int mapSize){
    float playerDensity = 0;
    int tileDepth = 2*mapSize/10;
    playerDensity = static_cast<int>(std::floor(nbPlayerAround/(tileDepth)));
    return playerDensity;
}

int getBehavior(int nbPlayerAround, size_t nbPlayer, int mapSize, int myposition){
    int playerDensity = getPlayerDensity(nbPlayerAround, mapSize);
    int attack;//assez de food, assez de canons, pas bcp d'or
    int flee;//bcp d'or, playerDensity élevée, peu de canons, moi ou joueur proche de la fin
    int behavior;
    return behavior;
}

void getMyResourceNeed(){
    //needFood 0
    //needGold 1
    //needCanons 2
    return;
}

//regarde les handcards de chaque joueur
//regarde les boathold de chaque joueur
//estime leur comportement
std::vector<int> getOtherPlayerBehavior(std::vector<state::Player *> playerList){

    std::vector<int> playerBehaviors; //needFood 0 needGold 1 needCanons 2

    return playerBehaviors;
}




std::string ai::DeepAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : ";
    playerName= getDeepName(&takenNamesIndex);
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



//choisit dé puis carte
//check ses hand cartes 
//prédit sa future position et celle des autres joueurs si dé connu (ils ont pas tous choisi ) ou sa
//
int ai::DeepAI::chooseCardFromHand(const std::vector<int>& handCards) {

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
    int bestOpponentIndex = 0;
    double highestScore = -std::numeric_limits<double>::infinity();
    
    std::vector<state::Player *> playerList = gameView->getPlayerList();

    for (size_t opponentIndex = 0; opponentIndex < listSize; ++opponentIndex) {
        double score = 0.0;

        state::Player* opponent = controlledPlayer->getOpponentsList().at(opponentIndex);

        if (opponent->getPlayerId()!=controlledPlayer->getPlayerId()) {

            for (state::BoatHold* boathold : opponent->getBoatHolds()) {
                if (boathold->hasResourceType("CANON")) {
                    score -= 0.5 * boathold->getQuantity();
                }
                if (boathold->hasResourceType("FOOD") && boathold->getQuantity() > 2) { //à modifier
                    score += 1;
                }
                if (boathold->hasResourceType("GOLD") && boathold->getQuantity() > 2) { //à modifier
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

ai::DeepAI::~DeepAI()
{
}
