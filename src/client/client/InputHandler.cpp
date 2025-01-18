#include "InputHandler.h"
#include "../../shared/state/BoatHold.h"
#include <iostream>
#include <string>
#include <limits>
#include "state.h"
#include "../client.h"

#define EXIT_GAME 0
#define LOCAL_MULTIPLAYER 1
#define ONLINE_MULTIPLAYER 2
#define DUEL_GAME 3

using state::BoatHold;

namespace client{

InputHandler::InputHandler(){
}

int InputHandler::getNumberofPlayers() {
    int playerNumber = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while (true) {
        std::cout << "Enter the number of players (2-6): ";
        while (waitingInput);

        try {
            playerNumber = stoi(userInput);
            std::cout << playerNumber << std::endl;

            if (playerNumber >= 2 && playerNumber <= 6) {
                isInputValid = true;
                waitingInput = false;
                return playerNumber;
            }
        }
        catch(std::invalid_argument e){
        }
        std::cout << "Invalid input. Please enter a number between 2 and 6.\n";
        waitingInput = true;
    }
}

std::string InputHandler::getPlayerName(int playerIndex){
    std::string playerName;

    userInput = "";
    isInputValid = false;
    isStringExpected = true;
    waitingInput = true;

    while (!isInputValid) {
        std::cout << "Enter name for player " << playerIndex+1 << ": ";
        while (waitingInput);
        playerName = userInput;
        isInputValid = true;
        std::cout << playerName << std::endl;
    }
    return playerName;
}


int InputHandler::getMapSize(){
    int mapSize = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = true;
    waitingInput = true;

    while (true) {
        std::cout << "Enter the size of the map: ";
        while (waitingInput);
        if (userInput.size() < 3){
            try {
                mapSize = stoi(userInput);

                if (abs(mapSize - 45) <= 15) {
                    isInputValid = true;
                    waitingInput = false;
                    std::cout << mapSize << std::endl;
                    return mapSize;
                }
            }
            catch(std::invalid_argument e){
            }
        }
        mapSize = 0; 
        std::cout << "Invalid map size. Please enter a value between 30 and 60." << std::endl;
        waitingInput = true;
    }
}


size_t InputHandler::selectUserBoatHold(size_t boatHoldCount, bool steal){
    size_t index = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while (true) {
        if(steal){
            std::cout << "You can steal one of " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : " << std::endl;
        }
        else{
            std::cout << "You have " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : " << std::endl;
        }

        while (waitingInput);
        try {
            index = stoi(userInput);

            if (index > 0 && index <= boatHoldCount) {
                isInputValid = true;
                waitingInput = false;
                std::cout << index << std::endl;
                return index-1;
            }
        }
        catch(std::invalid_argument e){
        }
        std::cout << "Invalid index. Please enter a number between 1 and " << boatHoldCount << "." << std::endl;
        waitingInput = true;
    }
}

bool InputHandler::confirmBoatHoldReplace(){
    std::string input;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    
    while (true) {
        std::cout << "This boathold contains other resources. Do you want to replace them ? (y/n) : ";
        std::cin >> input;

        while(waitingInput);
        input = userInput;

        if (input == "y" || input == "n") {
            isInputValid = true;
            return input == "y";
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
        waitingInput = true;
    }
}

int InputHandler::chooseCardFromHand(const std::vector<int>& handCards) {
    std::cout<<"Your 3 handCards:"<<std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while (true) {
        std::cout<<"Choose a card, enter an index between 1 and 3:"<<std::endl;
        while (waitingInput);
        try {
            choice = stoi(userInput);

            if (choice >=1 && choice <= 3) {
                isInputValid = true;
                waitingInput = false;
                std::cout << choice << std::endl;
                return handCards.at(choice-1);
            }
        }
        catch(std::invalid_argument e){
        }
        std::cout<<"Invalid input. Please enter a valid index (1-3)."<<std::endl;
        waitingInput = true;
    }
}

bool InputHandler::chooseTimeDice(int die1, int die2){
    std::string input;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while (true) {
        std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
                  << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
        while (waitingInput);
        input = userInput;

        if (input == "1" || input == "2") {
            isInputValid = true;
            return input == "1";
        }
        std::cout << "Entrée invalide. Veuillez entrer '1' ou '2'.\n";
        waitingInput = true;
    }
}

int InputHandler::chooseOpponent(size_t opponentsNb)
{
    size_t choice = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while (true) {
        std::cout<<"Choose an opponent, enter an index between 1 and "<< opponentsNb << std::endl;

        if (opponentsNb == 1){
            std::cout << "You had no choice, prepare to fight." << std::endl;
            waitingInput = false;
            isInputValid = true;
            return 0;
        }

        while (waitingInput);
        try {
            choice = stoi(userInput);

            if (choice >=1 && choice <= opponentsNb) {
                isInputValid = true;
                waitingInput = false;
                std::cout << choice << std::endl;
                return choice-1;
            }
        }
        catch(std::invalid_argument e){
        }
        std::cout<<"Invalid input. Please enter a valid index."<<std::endl;
        waitingInput = true;
    }
}

bool InputHandler::getInputValidation()
{
    return isInputValid;
}

bool InputHandler::getInputTypeIsString()
{
    return isStringExpected;
}

bool InputHandler::getWaitingInput() const
{
    return waitingInput;
}

void InputHandler::setWaitingInput(bool waitingInput)
{
    this->waitingInput = waitingInput;
}

void InputHandler::setUserInput(const std::string &userInput)
{
    this->userInput = userInput;
}

int InputHandler::chooseCanonNb(int totalNb){
    if (totalNb <= 0) {
        std::cout << "You don't have any available canons." << std::endl;
        return 0;
    }
    int chosenNb = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = true;
    waitingInput = true;

    while (true) {
        std::cout << "You have " << totalNb << " available canons. How many do you want to use ? ";

        while (waitingInput);
        if (userInput.size() < 3){
            try {
                chosenNb = stoi(userInput);
                if (chosenNb < 0) {
                    std::cout << "You cannot use a negative number of canons. " << std::endl;
                }
                else if (chosenNb > totalNb) {
                    std::cout << "You cannot use more canons than you possess. " << std::endl;
                }
                else {
                    isInputValid = true;
                    waitingInput = false;
                    std::cout << chosenNb << std::endl;
                    return chosenNb;
                }
            }
            catch(std::invalid_argument e){
            }
        }
        else {
            std::cout << "Invalid input. Please enter a number. " << std::endl;
        }
        waitingInput = true;
    }
}

int InputHandler::selectGameMode()
{
    std::string input;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    
    while (true) {
        std::cout << "What mode do you want to play ? (0 = exit, 1 = local, 2 = online)"/*, 3 = duel)"*/ << std::endl;

        while (waitingInput);
        input = userInput;

        if (input == "0" /*|| input == "exit"*/) {
            isInputValid = true;
            return EXIT_GAME;
        }
        else if (input == "1" /*|| input == "local"*/) {
            isInputValid = true;
            return LOCAL_MULTIPLAYER;
        }
        else if (input == "2" /*|| input == "online"*/) {
            isInputValid = true;
            return ONLINE_MULTIPLAYER;
        }
        /*else if (input == "3" || input == "duel") {
            isInputValid = true;
            return DUEL_MODE;
        }*/
        std::cout << "Invalid input. Please enter '0', '1', or '2'"/* or '3'." */<< std::endl;
        waitingInput = true;
    }
    return 0;
}

int InputHandler::selectLevelAI()
{
    Client::isPlayerAI = true;
    std::string setLevel;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while(true){
        std::cout << "What is the level of this AI ? (0 = cancel, 1 = easy, 2 = hard)"<< std::endl;;

        while (waitingInput);
        setLevel = userInput;

        if (setLevel == "0" /*|| setLevel == "cancel"*/) {
            Client::isPlayerTypeChosen=false;
            isInputValid = true;
            std::cout << "User cancelled" << std::endl;
            return 0;
        }
        else if (setLevel == "1" || setLevel == "random"){
            isInputValid = true;
            std::cout << "User selected 1 : randomAI" << std::endl;
            return 1;
        }
        else if (setLevel == "2" || setLevel == "heuristic"){
            isInputValid = true;
            std::cout << "User selected 2 : heuristicAI" << std::endl;
            return 2;
        }
        else if (setLevel == "3" || setLevel == "deep"){
            isInputValid = true;
            std::cout << "User selected 3 : deepAI" << std::endl;
            return 3;
        }
        else {
            std::cout << "Invalid input. Please enter '0', '1', or '2'"<< std::endl;
        }
        waitingInput = true;
    }
    return 1;
}

int InputHandler::pickAnAI(int playerIndex)
{
    std::string setAnAI;
    int SelectionAI = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;

    while(true){
        std::cout << "Is Player " << playerIndex+1 << " an AI ? (y/n)"<< std::endl;


        while (waitingInput);
        setAnAI = userInput;

        if (setAnAI == "n" /*|| setAnAI == "no"*/) {
            Client::isPlayerAI = false;
            Client::isPlayerTypeChosen=true;
            isInputValid = true;
            return 0;
        }
        else if (setAnAI == "y" /*|| setAnAI == "yes"*/) {
            Client::isPlayerAI = true;
            Client::isPlayerTypeChosen=true;
            isInputValid = true;
            SelectionAI = selectLevelAI();
            if (SelectionAI){
                return SelectionAI;
            }
        }
        else {
            std::cout << "Invalid input : this is a y/n question."<< std::endl;
        }
        waitingInput = true;
    }
}


}
