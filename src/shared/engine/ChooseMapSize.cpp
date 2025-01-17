#include "ChooseMapSize.h"
#include <iostream>

#define TREASURE 0
#define FOOD 1
#define GOLD 2

#define MAX_TREASURES 15

engine::ChooseMapSize::ChooseMapSize(int size) : size(size){

}

void const engine::ChooseMapSize::launchCommand (state::Game * GamePtr){
    if (GamePtr->map == nullptr) {
        GamePtr->map = new state::Map(size);
    } else {
        GamePtr->map->setSize(size);
        GamePtr->map->listOfTiles.clear();
    }
    
    int playerNumber = GamePtr->getPlayerList().size();
    GamePtr->map->listOfTiles.push_back(new state::Tile(0, "Port Royal", playerNumber));
    // other Tiles
    int treasureCount = 0;
    for (int i = 0; i < size-1; ++i) {
        int resource = TREASURE;
        //int cost = rand()%4;
        int cost = rand()%2+rand()%3; // to get a better repartition with less treasures and less cost-3
        //reroll the cost if there are no more treasures available :
        while (!cost && treasureCount > MAX_TREASURES){
            cost = rand()%2+rand()%3;
        }
        if (cost){
            resource = 1+(int)((rand()%3)/2);
        }
        state::Tile *tile;
        if (resource == TREASURE){
          tile = new state::Tile(cost, "Treasure", 0);
          tile->treasureAvailable=true;
          treasureCount++;
        }
        if (resource == FOOD){
          tile = new state::Tile(cost, "Food", 0);
        }
        if (resource == GOLD){
            tile = new state::Tile(cost, "Gold", 0);
        }
        GamePtr->map->listOfTiles.push_back(tile);
    }
    std::cout<<"Map initialized with " << std::to_string(GamePtr->map->getSize()) << " tiles."<< std::endl;
    GamePtr->setMapReady(true);
    std::cout <<"Map is ready"<<std::endl;
}

engine::ChooseMapSize::~ChooseMapSize(){}