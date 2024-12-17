#include "ChooseMapSize.h"
#include <iostream>

#define TREASURE 0
#define GOLD 1
#define FOOD 2


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
 //"Port Royal" : Start Tile : foodCost, goldCost, treasure, nbPlayer

    //state::Tile tile(0, "Port Royal", playerNumber);
    //GamePtr->map->listOfTiles.push_back(&tile);
    GamePtr->map->listOfTiles.push_back(new state::Tile(0, "Port Royal", playerNumber));
    // other Tiles
    for (int i = 0; i < size-1; ++i) {
        int resource = TREASURE;
        int cost = rand()%4;
        if (cost){
            resource = 1+rand()%2;
        }
        state::Tile *tile;
        if (resource == TREASURE){
          tile = new state::Tile(cost, "Treasure", 0);
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