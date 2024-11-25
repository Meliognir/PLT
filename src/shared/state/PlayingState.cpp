#include "PlayingState.h"
#include "Map.h"
#include "Tile.h"
#include "Player.h"
#include "GameConfigState.h"
#include "Game.h"
#include "../engine/ResourceManager.h"
#include "Gold.h"
#include "Food.h"
#include "Canon.h"
#include "../../client/client/InputHandler.h"
#include "../engine/DiceManager.h"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <utility> // Pour std::forward


#define TREASURE 0
#define GOLD 1
#define FOOD 2

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


//-------------------------
// Lucian works here
//-------------------------


namespace state {

  PlayingState::~PlayingState() {
    std::cout << "Playing state destructor called" << std::endl;
  }

//-----------------------------
// initializes the map and its tiles and initializes players' other parameters 
//-----------------------------
  void PlayingState::handle1() {
    client::InputHandler inputHandler;
    int mapSize = inputHandler.getMapSize();
    //-------------Initializes Map + tiles------------
    
    /*while(mapSize <= 1){
      std::cout << "Enter the size of the map: ";
      std::cin >> mapSize;
      if (std::cin.fail()) { 
          std::cin.clear();   
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
          std::cout << "Invalid input. Please enter a number." << std::endl;
          mapSize = 0; 
      } else if(mapSize <= 1){
        std::cout << "Invalid map size. Please enter a number higher than 1." << std::endl;
      }
    }*/
    if (game->map == nullptr) {
        game->map = new Map(mapSize);
    } else {
        game->map->setSize(mapSize);
        game->map->listOfTiles.clear();
    }

    int playerNumber = game->getPlayerList().size();
    // "Port Royal" : Start Tile : foodCost, goldCost, treasure, nbPlayer
    Tile tile(0, "Port Royal", playerNumber);
    game->map->listOfTiles.push_back(&tile);
    // other Tiles
    for (int i = 0; i < mapSize-1; ++i) {
      int resource = TREASURE;
      int cost = rand()%4;
      if (cost){
        resource = 1+rand()%2;
      }

      Tile *tile;
      if (resource == TREASURE){
        tile = new Tile(cost, "Treasure", 0);
      }
      if (resource == FOOD){
        tile = new Tile(cost, "Food", 0);
      }
      if (resource == GOLD){
        tile = new Tile(cost, "Gold", 0);
      }
      game->map->listOfTiles.push_back(tile);
    }

    //std::cout << "Map initialized with " << game->map->getSize() << " tiles." << std::endl;
    inputHandler.displayMessage("Map initialized with " + std::to_string(game->map->getSize()) + " tiles.");
    //-------------Initializes players' parameters------------
    const std::vector<Player*>& playingPlayers = game->getPlayerList();
    for (Player* player : playingPlayers) {
      player->setPosition(0);
      // Treasure(bonus, malus)
      std::vector<Treasure> initialTreasures = { Treasure(0, 0) };
      player->setTreasures(initialTreasures);

      // BoatHold()
      //définir setBoatHolds
      // Gold() + Food()
      //Un std::unique_ptr est un pointeur intelligent qui garantit 
      //qu'il ne peut y avoir qu'un seul propriétaire de l'objet 
      //pointé, assurant ainsi une gestion mémoire automatique et 
      //une prévention des fuites de mémoire.
      //En utilisant std::move, cela transfère directement l’objet 
      //au lieu d'en faire une copie, ce qui est essentiel pour les 
      //unique_ptr car ils ne peuvent pas être copiés. Sans std::move,
      //cela ne compilerait pas car un unique_ptr ne supporte pas la copie
      auto goldResource = make_unique<Gold>();
      engine::ResourceManager resource_manager;
      resource_manager.addResourcesToBoathold(player,std::move(goldResource), 3,1);
      auto foodResource = make_unique<Food>();
      resource_manager.addResourcesToBoathold(player,std::move(foodResource), 3,2);
      int i=1;
      for (BoatHold *bh: player->getBoatHolds()) {
        std::cout<< "BoatHold N°" << i << " : " ;
        bh->showContent();
        i++;
      }



      // print le type et nombre de ressource du boathold : void BoatHold::showContents()
      game->displayState();

      inputHandler.displayMessage("Player " + std::to_string(player->getPlayerId()) + " (" + player->getName() + ") initialized at position " + std::to_string(player->getPosition()));
    }
    inputHandler.displayMessage("Players initialized: " + std::to_string(playingPlayers.size()) + " players in the game.");
  }


  void PlayingState::handle2() {


      startingPlayerIndex = (startingPlayerIndex + 1) % playerCount;
    }
    //---Appel du handle1 du game Over


  }

}