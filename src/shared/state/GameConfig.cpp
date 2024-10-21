#include "GameConfig.h"
#include "Game.h"
#include "Player.h"
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
    std::vector<Player*> players;
  
    for (int i = 0; i < playerNumber; ++i) {
      std::string playerName;
      std::cout << "Enter name for player " << (i + 1) << ": ";
      std::cin >> playerName;
      //!!!!!!!!!!!!!!!!!!!!!!!
      Player* player = new Player(i + 1, playerName); // Player ID starts at 1
      //!!!!!!!!!!!!!!!!!!!!!!!
      player->setName(playerName);
      players.push_back(player);
      std::cout << "Player " << (i + 1) << " is named: " << playerName << std::endl;
    }

    //!!!!!!!!!!!!!!!!!!!!!!!
    Game game(nullptr, players); //see Game.h
    game.setPlayerList(players);
    //!!!!!!!!!!!!!!!!!!!!!!!
  }

//-----------------------------
//nothing
//-----------------------------
  void GameConfig::handle2() { 
  }

  GameConfig::~GameConfig() {
    std::cout << "GameConfig destructor called" << std::endl;
  }

} // namespace state
