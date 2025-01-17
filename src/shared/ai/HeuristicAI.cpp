#include "AI.h"
#include "HeuristicAI.h"
#include <iostream>
#include <cstdlib>
#include <limits>
#include <state/BoatHold.h>
#include <state/Game.h>
#include <state/Player.h>

#define HEURISTIC_PLACE_HOLDER 1

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ADD_FOOD 2
#define ADD_GOLD 3
#define ADD_CANONS 4

//------------------------------------------------------
// Ceci est une AI pacifique mais meilleure que RandomAI
//------------------------------------------------------

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
        int leastResourceAmount = SIZE_MAX;

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


// -changer client.cpp car il y a trop de répétition de code, cela devient difficile de gérer tous les cas de selectUserBoatHold
// -client.cpp devrait tout le temps appeler avec les 3 inputs, ce n'est pas le cas
// -l'IA devrait passer par des commandes dans engine pour modifier ses Boatholds
size_t ai::HeuristicAI::selectUserBoatHold(size_t boatHoldCount, std::string resType, int PlayerIndex, bool hasToPay) {
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


//IDEA : regarder les dés et tester les 3 combinaisons, même méthode que pour les dés dans la moitié des cas
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



//IDEA : regarder les 6 combinaisons
// avancer > gold > food > canon > reculer
bool ai::HeuristicAI::chooseTimeDice(int die1, int die2) {
    std::cout << "AI : Chose the dayDie. The Other will be the nightDie. (1 or 2)\n"
              << "Die 1 : " << die1 << " Die 2 : " << die2 << std::endl;
    int cardValue;
    state::ActionCard *actionCard;
    int actionType;
    int currentPos = controlledPlayer->getPosition();
    int currentDie;
    std::string resType;
    int resCost;
    int tempScore = 0;
    int maxScore = 0;
    int maxScoreDie;
    int malus = 0;

    int choice;

    for (size_t i = 0; i < controlledPlayer->getHandCards().size(); i++) { // 3 handCards

        for (int d = 0; d < 2; d++){ // die 1 or 2
            tempScore = 0;
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
                    if(resType == "Gold"){
                        malus = 1;
                    }
                    if(resType == "Food"){
                        malus = 2;
                    }
                    tempScore = tempScore - malus*resCost;
                    break;
                case MOVE_BACKWARD:
                    // reculer c'est grave
                    resType = gameView->getMap()->getResourceType(currentPos - currentDie);
                    resCost = gameView->getMap()->getResourceCost(currentPos - currentDie);
                    if(resType == "Gold"){
                        malus = 1;
                    }
                    if(resType == "Food"){
                        malus = 2;
                    }
                    tempScore = tempScore - malus*resCost*2;
                    break;
                case ADD_FOOD:
                    tempScore += currentDie*2;
                    break;
                case ADD_GOLD:
                    tempScore += currentDie*1;
                    break;
                case ADD_CANONS:
                    // les canons ne sont pas utiles
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


// L'AI met l'entièreté de ses canons en jeu, de toute manière elle n'aime pas la violence donc elle aura jeté ses canons avant
int ai::HeuristicAI::chooseCanonNb(int totalNb){
    return totalNb;
}

// L'AI choisie l'opposant en fonction d'un score qui favorise peu de canon, assez de gold et food
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
