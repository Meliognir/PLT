#include "InputHandler.h"
#include <iostream>
#include <string>
#include <limits>

namespace client{
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

InputHandler::InputHandler(){
}
}
