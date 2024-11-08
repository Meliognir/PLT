#include "Playing.h"
#include "Map.h"
#include "Tile.h"
#include "Player.h"
#include "GameConfig.h"
#include "Game.h"
#include <iostream>
#include <vector>

//-------------------------
// Lucian works here
//-------------------------


namespace state {
//-----------------------------
// initializes the map and its tiles and initializes players' other parameters 
//-----------------------------
  Playing::~Playing() {
    std::cout << "Playing state destructor called" << std::endl;
  }

  void Playing::handle1() { // initializes Map, tiles, players' parameters
    int mapSize = 0;
    
    while(mapSize <= 1){
      std::cout << "Enter the size of the map: ";
      std::cin >> mapSize;
      if(mapSize <= 1){
        std::cout << "Invalid map size" << std::endl;
      }
    }
    if (game->map == nullptr) {
        game->map = new Map(mapSize);
    } else {
        game->map->setSize(mapSize);
        game->map->listOfTiles.clear();
    }

    int playerNumber = game->getPlayerList().size();
    Tile tile(0, 0, false, playerNumber); // Start Tile : foodCost, goldCost, treasure, nbPlayer
    game->map->listOfTiles.push_back(tile);
    for (int i = 0; i < mapSize-1; ++i) { // other Tiles
      int tileFCost = rand()%4;
      int tileGCost = rand()%4;
      if(tileFCost != 0) {
        Tile tile(tileFCost, 0, false, 0);
      }
      if(tileFCost == 0 && tileGCost != 0) {
        Tile tile(0, tileGCost, false, 0);
      }
      if(tileFCost == 0 && tileGCost == 0) {
        Tile tile(0, 0, true, 0);
      }
      game->map->listOfTiles.push_back(tile);
    }

    std::cout << "Map initialized with " << game->map->getSize() << " tiles." << std::endl;


    const std::vector<Player*>& playingPlayers = game->getPlayerList(); //init players' parameters
    for (Player* player : playingPlayers) {
      player->setPosition(0);
      std::vector<Treasure> initialTreasures = { Treasure(0, 0)}; // Treasure(bonus, malus)
      std::vector<BoatHold> initialBoatHolds = { BoatHold(), BoatHold(), BoatHold(), BoatHold(), BoatHold(), BoatHold()}; // BoatHold()
      std::vector<ActionCard> initialCards = { ActionCard()}; // ActionCard (int cardID, Player * owner);
      player->setTreasures(initialTreasures);
      player->setBoatHolds(initialBoatHolds); // Player.cpp : void BoatHold::addResource(std::unique_ptr<Resources> newResource, int amount) calls selectBoatHold()
      player->setActionCard(initialCards);

      std::cout << "Player " << player->getPlayerId() << " (" << player->getName() << ") initialized at position " << player->getPosition() << std::endl;
    }
    std::cout << "Players initialized: " << playingPlayers.size() << " players in the game." << std::endl;
  }

//-------------------------
// Game Loop
//-------------------------
  void Playing::handle2() {
    const std::vector<Player*>& playingPlayers = game->getPlayerList();
    bool gameOver = false;
    int turnCount = 0;
    int playerCount = playingPlayers.size();
    int startingPlayerIndex = 0;
    int dice1 = 0;
    int dice2 = 0;
    bool diceBool = false;

    //gameTurn à enlever
    while (!gameOver) {
        std::cout << "Starting a new round in the Playerlist." << std::endl;
        startingPlayerIndex = turnCount % playerCount;

        Player* currentPlayer = playingPlayers[startingPlayerIndex];
          dice1 = rand() % 6 + 1;
          dice2 = rand() % 6 + 1;
          diceBool = currentPlayer->chooseTimeDice(dice1, dice2); // std::cout << "Day dice roll: " << game->dayDice << std::endl;
                                    // std::cout << "Night dice roll: " << game->nightDice << std::endl;
          if(diceBool){
            game->dayDice = dice1;
            game->nightDice = dice2;
          }
          else{
            game->dayDice = dice2;
            game->nightDice = dice1;
          }
          
          std::cout << "Player " << currentPlayer->getPlayerId() << " rolls the dice." << std::endl;
          currentPlayer->chooseTimeDice();
          std::cout << "Day dice roll: " << game->dayDice << ", Night dice roll: " << game->nightDice << std::endl;


        turnCount +=1;
          //player->setPosition(player->getPosition() + game->dayDice);
          //std::cout << "Player " << player->getPlayerId() << " (" << player->getName() << ") moves to position " << player->getPosition() << std::endl

        

        gameOver = game->checkGameEndCondition();
    }
  }
}