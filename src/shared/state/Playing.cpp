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
    int playerNumber=game->getPlayerList().size();
    Tile tile(0, 0, false, playerNumber); // foodCost, goldCost, treasure, nbPlayer
    game->map->listOfTiles.push_back(tile);
    for (int i = 0; i < mapSize; ++i) {
      int tileFCost=rand()%4;
      int tileGCost=rand()%4;
      playerNumber=game->getPlayerList().size();
      if(tileFCost!=0) {
        Tile tile(tileFCost, 0, false, playerNumber); // foodCost, goldCost, treasure, nbPlayer
        game->map->listOfTiles.push_back(tile);
      }
      if(tileFCost==0 && tileGCost!=0) {
        Tile tile(0, tileGCost, false, playerNumber); // foodCost, goldCost, treasure, nbPlayer
        game->map->listOfTiles.push_back(tile);
      }
      if(tileFCost==0 && tileGCost==0) {
        Tile tile(0, 0, true, playerNumber); // foodCost, goldCost, treasure, nbPlayer
        game->map->listOfTiles.push_back(tile);
      }
    }

    std::cout << "Map initialized with " << game->map->getSize() << " tiles." << std::endl;


    const std::vector<Player*>& playingPlayers = game->getPlayerList();
    for (Player* player : playingPlayers) {
      player->setPosition(0);
      std::cout << "Player " << player->getPlayerId() << " (" << player->getName() << ") initialized at position " << player->getPosition() << std::endl;
    }
    std::cout << "Players initialized: " << playingPlayers.size() << " players in the game." << std::endl;
  }

//-------------------------
// Game Loop
//-------------------------
  void Playing::handle2() {
    //the loop must start with the dices

  }
}