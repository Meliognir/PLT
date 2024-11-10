#include "GameConfig.h"
#include "Game.h"
#include "Player.h"
#include "Playing.h"
#include <iostream>
#include <vector>
#include <memory>

//-------------------------
// Lucian works here
//-------------------------


namespace state {
//-----------------------------
//asks for the number of player, instantiates Players and initializes their name
//-----------------------------
  void GameConfig::handle1() { 
    int playerNumber = 0;

    while(playerNumber < 2 || playerNumber > 6) {
        std::cout << "Enter the number of players: ";
        std::cin >> playerNumber;
        if (playerNumber < 2 || playerNumber > 6) {
            std::cout << "Invalid number of players. Please enter a number between 2 and 6." << std::endl;
        }
    }
    std::cout << "Number of players set to: " << playerNumber << std::endl;

    for (int i = 0; i < playerNumber; ++i) {
      std::string playerName;
      std::cout << "Enter name for player " << (i + 1) << ": ";
      std::cin >> playerName;
      Player* player = new Player(i + 1, playerName);
      std::vector<Player*> players = game->getPlayerList();
      players.push_back(player);
      game->setPlayerList(players);
    }
  }

//-----------------------------
//transition to Playing concrete state
//-----------------------------
  void GameConfig::handle2() {
    std::cout << "Transitioning to Playing state..." << std::endl;
    game->transitionTo(new Playing);
  }

  GameConfig::~GameConfig() {
    std::cout << "GameConfig destructor called" << std::endl;
  }

} // namespace state
