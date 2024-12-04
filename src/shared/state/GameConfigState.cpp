#include "GameConfigState.h"
#include "Game.h"
#include "Player.h"
#include "CaptainDiceState.h"
#include "../../client/client/InputHandler.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits> 

namespace state {
//-----------------------------
//asks for the number of player, instantiates Players and initializes their name
//-----------------------------
  void GameConfigState::handle1() { 
    client::InputHandler inputHandler;

    int playerNumber = inputHandler.getNumberofPlayers();
    std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;

    std::vector<Player*> players;
    for (int i = 0; i < playerNumber; ++i) {
        std::string playerName = inputHandler.getPlayerName(i + 1);
        Player* player = new Player(i + 1, playerName);
        players.push_back(player);
    }
    game->setPlayerList(players);
    /*int playerNumber = 0;

    while(playerNumber < 2 || playerNumber > 6) {
        std::cout << "Enter the number of players: ";
        std::cin >> playerNumber;
        if (std::cin.fail()) { 
          std::cin.clear();   
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
          std::cout << "Invalid input. Please enter a number between 2 and 6." << std::endl;
          playerNumber = 0; 
    } else if (playerNumber < 2 || playerNumber > 6) {
        std::cout << "Invalid number of players. Please enter a number between 2 and 6." << std::endl;
    }
    }
    std::cout << "Number of players set to: " << playerNumber << std::endl;
    std::vector<Player*> players={};
    for (int i = 0; i < playerNumber; ++i) {
      std::string playerName;
      std::cout << "Enter name for player " << (i + 1) << ": ";
      std::cin >> playerName;
      Player* player = new Player(i + 1, playerName);
      players.push_back(player);
    }
    game->setPlayerList(players);*/
  }

//-----------------------------
//transition to CaptainDice concrete state
//-----------------------------
  void GameConfigState::handle2() {

    std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
    game->transitionTo(new CaptainDiceState);
  }

  GameConfigState::~GameConfigState() {
    std::cout <<"GameConfig destructor called"<< std::endl;
  }

} 
