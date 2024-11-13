#include "Playing.h"
#include "Map.h"
#include "Tile.h"
#include "Player.h"
#include "GameConfig.h"
#include "Game.h"
#include "Resources.h"
#include "Gold.h"
#include "Food.h"
#include "Canon.h"
#include <iostream>
#include <vector>
#include <limits>

#define DAY true
#define NIGHT false

//-------------------------
// Lucian works here
//-------------------------


namespace state {

  Playing::~Playing() {
    std::cout << "Playing state destructor called" << std::endl;
  }

//-----------------------------
// initializes the map and its tiles and initializes players' other parameters 
//-----------------------------
  void Playing::handle1() {
    int mapSize = 0;
    //-------------Initializes Map + tiles------------
    while(mapSize <= 1){
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
    }
    if (game->map == nullptr) {
        game->map = new Map(mapSize);
    } else {
        game->map->setSize(mapSize);
        game->map->listOfTiles.clear();
    }

    int playerNumber = game->getPlayerList().size();
    // "Port Royal" : Start Tile : foodCost, goldCost, treasure, nbPlayer
    Tile tile(0, 0, false, playerNumber);
    game->map->listOfTiles.push_back(tile);
    // other Tiles
    for (int i = 0; i < mapSize-1; ++i) {
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

    //-------------Initializes players' parameters------------
    const std::vector<Player*>& playingPlayers = game->getPlayerList();
    for (Player* player : playingPlayers) {
      player->setPosition(0);
      // Treasure(bonus, malus)
      std::vector<Treasure> initialTreasures = { Treasure(0, 0) };
      player->setTreasures(initialTreasures);
      // BoatHold()
      std::vector<BoatHold *> initialBoatHolds(6);
      //définir setBoatHolds
      player->setBoatHolds(initialBoatHolds);
      // Gold() + Food()
      //Un std::unique_ptr est un pointeur intelligent qui garantit 
      //qu'il ne peut y avoir qu'un seul propriétaire de l'objet 
      //pointé, assurant ainsi une gestion mémoire automatique et 
      //une prévention des fuites de mémoire.
      //En utilisant std::move, cela transfère directement l’objet 
      //au lieu d'en faire une copie, ce qui est essentiel pour les 
      //unique_ptr car ils ne peuvent pas être copiés. Sans std::move,
      //cela ne compilerait pas car un unique_ptr ne supporte pas la copie
      auto goldResource = std::unique_ptr<Gold>();
      player->addResourcesToBoatHold(std::move(goldResource), 3);
      auto foodResource = std::unique_ptr<Food>();
      player->addResourcesToBoatHold(std::move(foodResource), 3);
      // print le type et nombre de ressource du boathold : void BoatHold::showContents()




      
      //std::vector<int> cardDeck = {0, 1, 2, 3, 5 , 6, 7, 8, 9}; // randomiser la pioche de chaque joueur
      //player->setActionCard(cardDeck);

      std::cout << "Player " << player->getPlayerId() << " (" << player->getName() << ") initialized at position " << player->getPosition() << std::endl;
    }
    std::cout << "Players initialized: " << playingPlayers.size() << " players in the game." << std::endl;
  }

//-------------------------
// Game Loop
//-------------------------
  void Playing::handle2() {
    const std::vector<Player*>& playingPlayers = game->getPlayerList();
    Player* currentPlayer;
    Player* activePlayer;
    int playerCount = playingPlayers.size();
    int startingPlayerIndex = 0;
    int activePlayerIndex = 0;

    bool gameOver = false;
    int turn = 0;
    bool current_time[2] = {DAY, NIGHT};
    
    int dice1 = 0;
    int dice2 = 0;
    bool diceBool = false;

    while (!gameOver) {
      //-------------Captain + Round------------
      std::cout << "Starting a new round in the Playerlist." << std::endl;
      Game::time = DAY;
      turn ++; game->setTurn(turn);
      currentPlayer = playingPlayers[startingPlayerIndex];
      game->setCaptainIndex(startingPlayerIndex);
      //-------------Day and night Dices------------
      std::cout << "Player " << currentPlayer->getPlayerId() << " rolls the dice." << std::endl;
      dice1 = rand() % 6 + 1;
      dice2 = rand() % 6 + 1;
      diceBool = currentPlayer->chooseTimeDice(dice1, dice2);
      if(diceBool){
        // dayDie and nightDie are static => are the same and shared by every instance of Game, have no setter or getter
        // you can also write : Game::dayDie = ... , it will modify dayDie in "game" : instance of Game
        game->dayDie = dice1;
        game->nightDie = dice2;
      }
      else{
        game->dayDie = dice2;
        game->nightDie = dice1;
      }
      //-------------Every Player choose 1 Card in their own cardDeck------------
      for (int i = 0; i < playerCount; i++) {
        activePlayerIndex = (startingPlayerIndex + i) % playerCount;
        activePlayer = playingPlayers[activePlayerIndex];
        std::cout << "Player " << activePlayer->getPlayerId() << "'s turn. Choose your card wisely." << std::endl;
        activePlayer->chooseCard();
      }
      //-------------Every Player execute day and night Actions of their chosen card------------
      for (int i = 0; i < playerCount; i++) {
        Game::time = current_time[i];
        activePlayerIndex = (startingPlayerIndex + i) % playerCount;
        activePlayer = playingPlayers[activePlayerIndex];
        std::cout << "Player " << activePlayer->getPlayerId() << "'s turn. Execute your Action. Dew it." << std::endl;
        // add combat logic in Player.cpp
        activePlayer->playTurn();
      }

      startingPlayerIndex = (startingPlayerIndex + 1) % playerCount;

      gameOver = game->checkGameEndCondition();
    }
  }
}