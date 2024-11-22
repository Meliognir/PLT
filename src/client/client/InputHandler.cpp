#include "InputHandler.h"
#include <iostream>
#include <string>
#include <limits>

namespace client{

InputHandler::InputHandler(){
}

int client::InputHandler::getNumberofPlayers(){
    int playerNumber = 0;
    while (playerNumber < 2 || playerNumber > 6) {
        std::cout << "Enter the number of players: ";
        std::cin >> playerNumber;

        if (std::cin.fail()) {
            std::cin.clear();   
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 2 and 6.\n";
            playerNumber = 0;
        } else if (playerNumber < 2 || playerNumber > 6) {
            std::cout << "Invalid number of players. Please enter a number between 2 and 6.\n";
        }
    }
    return playerNumber;
}

std::string client::InputHandler::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player " << playerIndex << ": ";
    std::cin >> playerName;
    return playerName;
}

void client::InputHandler::displayMessage(const std::string &message){
    std::cout << message << std::endl;
}

int InputHandler::getMapSize(){
    int mapSize = 0;
        while (mapSize <= 1) {
            std::cout << "Enter the size of the map: ";
            std::cin >> mapSize;
            if (std::cin.fail()) { 
                std::cin.clear();   
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please enter a number." << std::endl;
                mapSize = 0; 
            } else if (mapSize <= 1) {
                std::cout << "Invalid map size. Please enter a number higher than 1." << std::endl;
            }
        }
    return mapSize;
}
size_t InputHandler::selectUserBoatHold(size_t boatHoldCount){
    size_t index = 0;
    while (true) {
        std::cout << "You have " << boatHoldCount << " BoatHolds. Pick one (1-" << boatHoldCount << ") : ";
        std::cin >> index;
        if (index < 1 || index > boatHoldCount) {
            std::cout << "Invalid index. Please enter a number between 1 and " << boatHoldCount << ".\n";
            continue;
        }
        return index;
    }
}

bool InputHandler::confirmBoatHoldReplace(){
    std::string input;
    while (true) {
        std::cout << "This boathold contains other resources. Do you want to replace them ? (y/n) : ";
        std::cin >> input;

        if (input == "y" || input == "n") {
            return input == "y";
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    }
}

int InputHandler::chooseCardFromHand(const std::vector<int>& handCards) {
    displayMessage("Your 3 handCards:");
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice = 0;
    while (true) {
        displayMessage("Choose a card, enter an index between 1 and 3:");
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayMessage("Invalid input. Please enter a valid index (1-3).");
        } else {
            return choice - 1;
        }
    }
}

}
