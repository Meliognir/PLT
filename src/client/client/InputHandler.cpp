#include "InputHandler.h"
#include <iostream>
#include <string>
#include <limits>
#include "state.h"

namespace client{

InputHandler::InputHandler(){
}

int client::InputHandler::getNumberofPlayers() {
    int playerNumber = 0;

    while (true) {
        std::cout << "Enter the number of players (2-6): ";
        std::cin >> playerNumber;

        if (!std::cin.fail() && playerNumber >= 2 && playerNumber <= 6) {
            break;
        }

        std::cin.clear();   
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number between 2 and 6.\n";
    }

    return playerNumber;
}

std::string client::InputHandler::getPlayerName(int playerIndex){
    std::string playerName;
    std::cout << "Enter name for player " << playerIndex+1 << ": ";
    std::cin >> playerName;
    return playerName;
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
    std::cout<<"Your 3 handCards:"<<std::endl;
    for (size_t i = 0; i < handCards.size(); ++i) {
        std::cout << i + 1 << ". " << handCards[i] << std::endl;
    }

    int choice = 0;
    while (true) {
        std::cout<<"Choose a card, enter an index between 1 and 3:"<<std::endl;
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 3) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout<<"Invalid input. Please enter a valid index (1-3)."<<std::endl;
        } else {
            return choice - 1;
        }
    }
}

bool InputHandler::chooseTimeDice(int die1, int die2){
    std::string input;
    while (true) {
        std::cout << "Choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n"
                  << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
        std::cin >> input;
        if (input == "1" || input == "2") {
            break;
        }
        std::cout << "Entrée invalide. Veuillez entrer '1' ou '2'.\n";
    }
    return input == "1";
}
int InputHandler::chooseCanonNb(int totalNb){
    if (totalNb <= 0) {
        std::cout << "You don't have any available canons." << std::endl;
        return 0;
    }
    int chosenNb = 0;
    while (true) {
        std::cout << "You have " << totalNb << " available canons. How many do you want to use ? ";
        std::cin >> chosenNb;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a number. " << std::endl;
        } else if (chosenNb < 0) {
            std::cout << "You cannot use a negative number of canons. " << std::endl;
        } else if (chosenNb > totalNb) {
            std::cout << "You cannot use more canons than you possess. " << std::endl;
        } else {
            break; 
        }
    }
    return chosenNb;
}


}
