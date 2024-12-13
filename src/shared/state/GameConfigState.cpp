#include "GameConfigState.h"
#include "Game.h"
#include "Player.h"
#include "CaptainDiceState.h"
#include "Gold.h"
#include "Food.h"
#include "../../client/client/InputHandler.h"
#include "../engine/ResourceManager.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits> 

#define TREASURE 0
#define GOLD 1
#define FOOD 2

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
namespace state {
//-----------------------------
//asks for the number of player, instantiates Players and initializes their name
//-----------------------------
  void GameConfigState::handle() {

    int CaptainIndex = 0; // set to 0 here and in CardActionState

    // int playerNumber = inputHandler.getNumberofPlayers();
    // std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;

    // std::vector<Player*> players;
    // for (int i = 0; i < playerNumber; ++i) {
    //     std::string playerName = inputHandler.getPlayerName(i + 1);
    //     Player* player = new Player(i + 1, playerName);
    //     players.push_back(player);
    // }
    // game->setPlayerList(players);
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

    //int mapSize = inputHandler.getMapSize();//A vire
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
    // if (game->map == nullptr) {
    //     game->map = new Map(mapSize);
    // } else {
    //     game->map->setSize(mapSize);
    //     game->map->listOfTiles.clear();
    // }

    //int playerNumber = game->getPlayerList().size();
    // "Port Royal" : Start Tile : foodCost, goldCost, treasure, nbPlayer
    // Tile tile(0, "Port Royal", playerNumber);
    // game->map->listOfTiles.push_back(&tile);
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
    std::cout<<"Map initialized with " << std::to_string(game->map->getSize()) << " tiles."<< std::endl;
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
      engine::ResourceManager resource_manager;//A vire
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

      std::cout<<"Player " << std::to_string(player->getPlayerId()) <<" (" + player->getName() << ") initialized at position " << std::to_string(player->getPosition())<< std::endl;
    }
    std::cout<<"Players initialized: " << std::to_string(playingPlayers.size()) << " players in the game."<< std::endl;

    std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
    game->transitionTo(new CaptainDiceState);
  }

  GameConfigState::~GameConfigState() {
    std::cout <<"GameConfig destructor called"<< std::endl;
  }

} 
