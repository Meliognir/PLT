#include "Map.h"

namespace state {

void Map::setSize(int size){
    size = size;
}

int Map::getSize() const{
    return size;
}

Map::~Map(){
}

Map::Map(int size){
    listOfTiles[0] = Tile(0, 0, false, 0); 
    listOfTiles[1] = Tile(2, 0, false, 0); 
    listOfTiles[2] = Tile(3, 0, false, 0); 
    listOfTiles[3] = Tile(2, 0, false, 0);
    listOfTiles[4] = Tile(0, 0, false, 0); 
    listOfTiles[5] = Tile(0, 2, false, 0);
    listOfTiles[6] = Tile(0, 3, false, 0); 
    listOfTiles[7] = Tile(1, 0, false, 0);
    listOfTiles[8] = Tile(4, 0, false, 0); 
    listOfTiles[9] = Tile(0, 0, false, 0); 
    setSize(10);
}
}