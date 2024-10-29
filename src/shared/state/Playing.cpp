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
    for (int i = 0; i < mapSize; ++i) {
      Tile tile(1, 1, false, 0); // foodCost, goldCost, treasure, nbPlayer
      game->map->listOfTiles.push_back(tile);
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
// Other
//-------------------------
  void Playing::handle2() {

}
}