#include "GameConfig.h"
#include <iostream>

  state::GameConfig::~GameConfig() {
    std::cout << "GameConfig destructor called" << std::endl;
  }

  void state::GameConfig::handle1() { //setPlayerNumber
    int playerNumber;
    std::cout << "Enter the number of players: ";
    std::cin >> playerNumber;
    if (playerNumber < 2 || playerNumber > 6) {
      std::cout << "Invalid number of players. Please enter a number between 2 and 6." << std::endl;
      return;
    }
    std::cout << "Number of players set to: " << playerNumber << std::endl;
  }

  void state::GameConfig::handle2() { //setPlayerName
    int playerNumber;
    std::cout << "How many players' names do you want to set?: ";
    std::cin >> playerNumber;
    for (int i = 0; i < playerNumber; ++i) {
      std::string playerName;
      std::cout << "Enter name for player " << (i + 1) << ": ";
      std::cin >> playerName;
      std::cout << "Player " << (i + 1) << " is named: " << playerName << std::endl;
    }
  }

