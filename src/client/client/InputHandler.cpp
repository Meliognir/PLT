#include "InputHandler.h"
#include "../../shared/state/BoatHold.h"
#include <iostream>
#include <string>
#include <limits>
#include <chrono>
#include <thread>
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
    int timer = 12;

    while (true) {
        std::cout << "Enter the number of players (2-6): " << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }

        try {
            playerNumber = stoi(std::string(1, userInput[0]));
            std::cout << playerNumber << std::endl;

            if (playerNumber >= 2 && playerNumber <= 6) {
                isInputValid = true;
                waitingInput = false;
                return playerNumber;
            }
        }
        catch(std::invalid_argument e){
        }
        std::cout << "Invalid input. Please enter a number between 2 and 6.\n" << std::endl;
        waitingInput = true;
    int timer = 12;
    }
}

std::string InputHandler::getPlayerName(int playerIndex){
    std::string playerName;

    userInput = "";
    isInputValid = false;
    isStringExpected = true;
    waitingInput = true;
    int timer = 12;

    while (!isInputValid) {
        std::cout << "Enter name for player " << playerIndex+1 << ": " << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
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
    int timer = 12;

    while (true) {
        std::cout << "Enter the size of the map: " << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
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
    int timer = 12;
    }
}


size_t InputHandler::selectUserBoatHold(size_t boatHoldCount, bool steal){
    size_t index = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    int timer = 12;

    while (true) {
        if(steal){
            std::cout << "You can steal one of " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : " << std::endl;
        }
        else{
            std::cout << "You have " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : " << std::endl;
        }

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        try {
            index = stoi(std::string(1, userInput[0]));

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
    int timer = 12;
    }
}

bool InputHandler::confirmBoatHoldReplace(){
    std::string input;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    int timer = 12;
    
    while (true) {
        std::cout << "This boathold contains other resources. Do you want to replace them ? (y/n) : " << std::endl;
        std::cin >> input;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        input = userInput;

        if (input == "y" || input == "n") {
            isInputValid = true;
            return input == "y";
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n" << std::endl;
        waitingInput = true;
    int timer = 12;
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
    int timer = 12;

    while (true) {
        std::cout<<"Choose a card, enter an index between 1 and 3:"<<std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        try {
            choice = stoi(std::string(1, userInput[0]));

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
    int timer = 12;
    }
}

bool InputHandler::chooseTimeDice(int die1, int die2){
    std::string input;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    int timer = 12;

    while (true) {
        std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
                  << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        input = userInput;

        if (input == "1" || input == "2") {
            isInputValid = true;
            return input == "1";
        }
        std::cout << "Entrée invalide. Veuillez entrer '1' ou '2'.\n" << std::endl;
        waitingInput = true;
    int timer = 12;
    }
}

int InputHandler::chooseOpponent(size_t opponentsNb)
{
    size_t choice = 0;

    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    int timer = 12;

    while (true) {
        std::cout<<"Choose an opponent, enter an index between 1 and "<< opponentsNb << std::endl;

        if (opponentsNb == 1){
            std::cout << "You had no choice, prepare to fight." << std::endl;
            waitingInput = false;
            isInputValid = true;
            return 0;
        }

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        try {
            choice = stoi(std::string(1, userInput[0]));

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
    int timer = 12;
    }
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
    int timer = 12;

    while (true) {
        std::cout << "You have " << totalNb << " available canons. How many do you want to use ? " << std::endl;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
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
    int timer = 12;
    }
}

int InputHandler::selectGameMode()
{
    std::string input;

    shouldStartListening = false;
    userInput = "";
    isInputValid = false;
    isStringExpected = false;
    waitingInput = true;
    int timer = 12;
    
    while (true) {
        std::cout << "What mode do you want to play ? (0 = exit, 1 = local, 2 = online)"/*, 3 = duel)"*/ << std::endl;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        input = userInput;

        if (input == "0" || input == "exit") {
            isInputValid = true;
            return EXIT_GAME;
        }
        else if (input == "1" || input == "local") {
            isInputValid = true;
            return LOCAL_MULTIPLAYER;
        }
        else if (input == "2" || input == "online") {
            isInputValid = true;
            return ONLINE_MULTIPLAYER;
        }
        /*else if (input == "3" || input == "duel") {
            isInputValid = true;
            return DUEL_MODE;
        }*/
        std::cout << "Invalid input. Please enter '0', '1', or '2'"/* or '3'." */<< std::endl;
        waitingInput = true;
    int timer = 12;
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
    int timer = 12;

    while(true){
        std::cout << "What is the level of this AI ? (0 = cancel, 1 = easy, 2 = medium, 3 = hard)"<< std::endl;;

        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        setLevel = userInput;

        if (setLevel == "0" || setLevel == "cancel") {
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
            std::cout << "Invalid input. Please enter '0', '1', '2' or '3'"<< std::endl;
        }
        waitingInput = true;
    int timer = 12;
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
    int timer = 12;

    while(true){
        std::cout << "Is Player " << playerIndex+1 << " an AI ? (y/n)"<< std::endl;


        auto startTime = std::chrono::high_resolution_clock::now();
        auto endTime = std::chrono::high_resolution_clock::now();
        while (waitingInput){
            endTime = std::chrono::high_resolution_clock::now();
            if (shouldStartListening){
                if (timer > 10){
                    std::cout << "Please enter your input here :" << std::endl;
                    waitingInput = false;
                    std::cin >> userInput;
                }
                else {
                    if (timer > 3){
                        std::cout << "The signal from the render window was lost.\nPlease wait " << 12-timer << " seconds so you can enter your inputs here." << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    }
                }
                timer = (std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime)).count();
            }
            else {
                if (timer > 3){
                    std::cout << "You should play in the render window !" << std::endl;
                }
                timer = 0;
                startTime = std::chrono::high_resolution_clock::now();
                shouldStartListening = true;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
        setAnAI = userInput;

        if (setAnAI == "n" || setAnAI == "no") {
            Client::isPlayerAI = false;
            Client::isPlayerTypeChosen=true;
            isInputValid = true;
            return 0;
        }
        else if (setAnAI == "y" || setAnAI == "yes") {
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
    int timer = 12;
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

void InputHandler::setShouldStartListening(bool shouldStartListening){
    this->shouldStartListening = shouldStartListening;
}


}
