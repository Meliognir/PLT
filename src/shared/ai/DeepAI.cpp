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

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ADD_FOOD 2
#define ADD_GOLD 3
#define ADD_CANONS 4

std::vector <int> ai::DeepAI::takenNamesIndex = {};

std::string getDeepName(std::vector <int> *takenNamesIndex){
    std::vector <std::string> nameList = {"Doctor Who", "Doctor Chopper", "Doctor Strange", "Doctor Frankenstein", "Doctor Watson", "Doctor House", "Doctor Heisenberg"};
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
// int getPlayerDensity(int nbPlayerAround, int mapSize){
//     float playerDensity = 0;
//     //profondeur de densité
//     int tileDepth = 2*mapSize/10;
//     playerDensity = static_cast<int>(std::floor(nbPlayerAround/(tileDepth)));
//     return playerDensity;
// }

// int getBehavior(int nbPlayerAround, size_t nbPlayer, int mapSize, int myposition){
//     int playerDensity = getPlayerDensity(nbPlayerAround, mapSize);
//     int attack;//assez de food, assez de canons, pas bcp d'or
//     int flee;//bcp d'or, playerDensity élevée, peu de canons, moi ou joueur proche de la fin
//     int behavior;
//     return behavior;
// }

// void getMyResourceNeed(){
//     //needFood 0
//     //needGold 1
//     //needCanons 2
//     return;
// }

//regarde les handcards de chaque joueur
//regarde les boathold de chaque joueur
//estime leur comportement
// std::vector<int> getOtherPlayerBehavior(std::vector<state::Player *> playerList){

//     std::vector<int> playerBehaviors; //needFood 0 needGold 1 needCanons 2

//     return playerBehaviors;
// }




std::string ai::DeepAI::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player : ";
    playerName= getDeepName(&takenNamesIndex);
    return playerName;
}

void removeOneBoatHoldDeep(size_t boatHoldCount, std::vector<state::BoatHold *> controlledBoatHold, std::string resToAdd){
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
        int leastResourceAmount = 1000;

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
                boatHoldWithLeastResources->removeResource(leastResourceAmount); // à faire par l'engine
                std::cout << "AI : Removed resources (Gold or Food) from BoatHold with the least resources." << std::endl;
            }
        }
        else{
            std::cout << "AI : Error failed to find BoatHold with the least resources." << std::endl;
        }
    }
}


size_t ai::DeepAI::selectUserBoatHold(size_t boatHoldCount, std::string resType, int PlayerIndex, bool hasToPay){
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
                    removeOneBoatHoldDeep(boatHoldCount, controlledBoatHold, resType);
                }
            }
        }
        // StealState : Voler un Boathold avec des food ou du gold de mon adversaire si je gagne un duel
        if(stateId == 8){

            // Voler loser player donné par client.cpp
//IDEA : voler gold, food si j'ai besoin de gold, food
            if(PlayerIndex != -1){
                std::cout << "AI : Stealing loser's Resources." << std::endl;

                state::Player* loser = gameView->getPlayerList().at(PlayerIndex);
                std::vector<state::BoatHold *> boatholdsToSteal = loser->getBoatHolds();

                // Calculer la Ressource avec le plus de quantité de Gold ou Food
                int i = 0;
                int maxAmount = 0;
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
                        removeOneBoatHoldDeep(boatHoldCount, controlledBoatHold, resType);
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



// ajouter prédiction de la position des autres joueurs si dé connu ( ils n'ont peut-être pas tous choisi encore leur carte )
// utiliser canonAmount
int ai::DeepAI::chooseCardFromHand(const std::vector<int>& handCards) {
    
    std::cout << "AI : My 3 handCards:" << std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int cardValue;
    state::ActionCard *actionCard;
    int actionType;
    int currentPos = controlledPlayer->getPosition();
    int currentDie;
    std::string resType;
    int resCost;
    int tempScore = 0;
    int maxScore = -1000;
    int maxScoreCard;
    int malus = 0;
    int amount, foodAmount, goldAmount, canonAmount;
    std::vector<state::BoatHold *> controlledBoatHold = controlledPlayer->getBoatHolds();
    std::vector<state::Player *> playerList = gameView->getPlayerList();

    for (int i = 0; i < 3; i++) { // 3 handCards

        tempScore = 0;
        foodAmount = 0;
        goldAmount = 0;
        canonAmount = 0;
        for (state::BoatHold* bh : controlledBoatHold) {
            if (bh->getResourceType() == "Food") {
                foodAmount += bh->getQuantity();
            }
            if (bh->getResourceType() == "Gold") {
                goldAmount += bh->getQuantity();
            }
            if (bh->getResourceType() == "Canon") {
                canonAmount += bh->getQuantity();
            }
        }

        for (int j = 0; j < 2; j++){ // day or night

            cardValue = controlledPlayer->getHandCards().at(i);
            actionCard = state::Game::collectionOfCards.at(cardValue);
            if(j == 0){
                currentDie = gameView->dayDie;
                actionType = actionCard->getDayAction();
            }
            if(j == 1){
                currentDie = gameView->nightDie;
                actionType = actionCard->getNightAction();
            }

            switch (actionType)
            {
            case MOVE_FORWARD:
                resType = gameView->getMap()->getResourceType(currentPos + currentDie);
                resCost = gameView->getMap()->getResourceCost(currentPos + currentDie);
                if (resType == "Gold") {
                    goldAmount -= resCost;
                    amount = goldAmount;
                }
                if (resType == "Food") {
                    foodAmount -= resCost;
                    amount = foodAmount;
                }
                if(resType == "Gold"){
                    malus = 1;
                }
                if(resType == "Food"){
                    malus = 1;
                }
                tempScore = tempScore - malus*resCost + malus*amount;
                break;
            case MOVE_BACKWARD:
                // reculer c'est grave
                resType = gameView->getMap()->getResourceType(currentPos - currentDie);
                resCost = gameView->getMap()->getResourceCost(currentPos - currentDie);
                if (resType == "Gold") {
                    goldAmount -= resCost;
                    amount = goldAmount;
                }
                if (resType == "Food") {
                    foodAmount -= resCost;
                    amount = foodAmount;
                }
                if(resType == "Gold"){
                    malus = 1;
                }
                if(resType == "Food"){
                    malus = 1;
                }
                tempScore = tempScore - (malus*resCost - malus*amount)*2;
                break;
            case ADD_FOOD:
                tempScore += currentDie*1;
                break;
            case ADD_GOLD:
                tempScore += currentDie*1;
                break;
            case ADD_CANONS:
                tempScore -= 1;
                break;
            default:
                std::cout << "AI : Error getting action type." << std::endl;
                break;
            }

        }    
        if(tempScore > maxScore){
            maxScore = tempScore;
            maxScoreCard = i;
        }
        
    }

    return maxScoreCard;
}


// Regarder (en plus par rapport à l'heuristic) mes Boatholds et voir si je peux payer sur le jour et la nuit cumulés
bool ai::DeepAI::chooseTimeDice(int die1, int die2){

    std::cout << "AI : Chose the dayDie. The Other will be the nightDie. (1 or 2)\n"
              << "Die 1 : " << die1 << " Die 2 : " << die2 << std::endl;

    int cardValue;
    state::ActionCard *actionCard;
    int actionType;
    int currentPos = controlledPlayer->getPosition();
    int currentDie;
    std::string resType;
    int resCost;
    double tempScore = 0;
    double maxScore = 0;
    int maxScoreDie;
    int malus = 0;
    int amount, foodAmount, goldAmount, canonAmount;
    double maxDuelScore, duelScore;
    int oppCanon = 0, oppGold = 0, oppFood = 0;
    std::vector<state::BoatHold *> controlledBoatHold = controlledPlayer->getBoatHolds();
    std::vector<state::Player *> playerList = gameView->getPlayerList();

    for (int i = 0; i < 3; i++) { // 3 handCards

        for (int d = 0; d < 2; d++){ // die 1 or 2

            tempScore = 0;
            foodAmount = 0;
            goldAmount = 0;
            canonAmount = 0;
            for (state::BoatHold* bh : controlledBoatHold) {
                if (bh->getResourceType() == "Food") {
                    foodAmount += bh->getQuantity();
                }
                if (bh->getResourceType() == "Gold") {
                    goldAmount += bh->getQuantity();
                }
                if (bh->getResourceType() == "Canon") {
                    canonAmount += bh->getQuantity();
                }
            }

            for (int j = 0; j < 2; j++){ // day or night

                cardValue = controlledPlayer->getHandCards().at(i);
                actionCard = state::Game::collectionOfCards.at(cardValue);

                if(d == 0){
                    if(j == 0){
                        currentDie = die1;
                        actionType = actionCard->getDayAction();
                    }
                    if(j == 1){
                        currentDie = die2;
                        actionType = actionCard->getNightAction();
                    }
                }
                if(d == 1){
                    if(j == 0){
                        currentDie = die2;
                        actionType = actionCard->getDayAction();
                    }
                    if(j == 1){
                        currentDie = die1;
                        actionType = actionCard->getNightAction();
                    }
                }

                switch (actionType)
                {
                case MOVE_FORWARD:
                    resType = gameView->getMap()->getResourceType(currentPos + currentDie);
                    resCost = gameView->getMap()->getResourceCost(currentPos + currentDie);
                    amount = 0;
                    // Regarder mes Boatholds et voir si je peux payer sur le jour et la nuit cumulés
                    if (resType == "Gold") {
                        goldAmount -= resCost;
                        amount = goldAmount;
                    }
                    if (resType == "Food") {
                        foodAmount -= resCost;
                        amount = foodAmount;
                    }
                    if(resType == "Gold"){
                        malus = 1;
                    }
                    if(resType == "Food"){
                        malus = 1;
                    }
                    tempScore = tempScore - malus*resCost + malus*amount;
                    // faire un score pour les duels
                    maxDuelScore = -1000; duelScore = 0;
                    oppCanon = 0; oppGold = 0; oppFood = 0;
                    for (int k = 0; k < playerList.size(); k++) {
                        state::Player* opponent = playerList.at(k);
                        if (opponent->getPlayerId() != controlledPlayer->getPlayerId() && opponent->getPosition() == (currentPos + currentDie)){
                            for (state::BoatHold* bh : opponent->getBoatHolds()) {
                                if (bh->hasResourceType("Canon")) {
                                    oppCanon += bh->getQuantity();
                                }
                                if (bh->hasResourceType("Gold")) {
                                    oppGold += bh->getQuantity();
                                }
                                if (bh->hasResourceType("Food")) {
                                    oppFood += bh->getQuantity();
                                }
                                duelScore = duelScore + 0.5*(oppFood + oppGold) - oppCanon + canonAmount;
                                if(duelScore > maxDuelScore){
                                    maxDuelScore = duelScore;
                                }
                            }
                        }   
                    }
                    tempScore += maxDuelScore;
                    break;
                case MOVE_BACKWARD:
                    // reculer c'est grave
                    resType = gameView->getMap()->getResourceType(currentPos - currentDie);
                    resCost = gameView->getMap()->getResourceCost(currentPos - currentDie);
                    if (resType == "Gold") {
                        goldAmount -= resCost;
                        amount = goldAmount;
                    }
                    if (resType == "Food") {
                        foodAmount -= resCost;
                        amount = foodAmount;
                    }
                    if(resType == "Gold"){
                        malus = 1;
                    }
                    if(resType == "Food"){
                        malus = 1;
                    }
                    tempScore = tempScore - (malus*resCost - malus*amount)*2;
                    // faire un score pour les duels
                    maxDuelScore = -1000; duelScore = 0;
                    oppCanon = 0; oppGold = 0; oppFood = 0;
                    for (int k = 0; k < playerList.size(); k++) {
                        state::Player* opponent = playerList.at(k);
                        if (opponent->getPlayerId() != controlledPlayer->getPlayerId() && opponent->getPosition() == (currentPos - currentDie)){
                            for (state::BoatHold* bh : opponent->getBoatHolds()) {
                                if (bh->hasResourceType("Canon")) {
                                    oppCanon += bh->getQuantity();
                                }
                                if (bh->hasResourceType("Gold")) {
                                    oppGold += bh->getQuantity();
                                }
                                if (bh->hasResourceType("Food")) {
                                    oppFood += bh->getQuantity();
                                }
                                duelScore = duelScore + 0.5*(oppFood + oppGold) - oppCanon + canonAmount;
                                if(duelScore > maxDuelScore){
                                    maxDuelScore = duelScore;
                                }
                            }
                        }   
                    }
                    tempScore += maxDuelScore;
                    break;
                case ADD_FOOD:
                    tempScore += currentDie*1;
                    break;
                case ADD_GOLD:
                    tempScore += currentDie*1;
                    break;
                case ADD_CANONS:
                    tempScore -= 1;
                    break;
                default:
                    std::cout << "AI : Error getting action type." << std::endl;
                    break;
                }

            }
            if(tempScore > maxScore){
                maxScore = tempScore;
                maxScoreDie = d;
            }
        }
    }
    if(maxScoreDie == 0){
        return 1; // die1 day die
    }
    else{
        return 0; // die1 night die
    }
}

int ai::DeepAI::chooseCanonNb(int totalNb){
    return totalNb;
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
                if (boathold->hasResourceType("Canon")) {
                    score -= 0.5 * boathold->getQuantity();
                }
                if (boathold->hasResourceType("Food") && boathold->getQuantity() > 2) { //à modifier
                    score += 1;
                }
                if (boathold->hasResourceType("Gold") && boathold->getQuantity() > 2) { //à modifier
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
