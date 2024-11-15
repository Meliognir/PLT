#include "Map.h"

namespace state {

Map::~Map(){
}

Map::Map(int size){
    //test
    setSize(size);
}

void Map::setSize(int size){
    this->size = size;
}

int Map::getSize() const{
    return size;
}

std::string Map::getResourceType (int position) {
   return listOfTiles.at(position)->getTileResource();
}

int Map::getResourceCost (int position) {
    if (getResourceType(position)=="Food") {
        return listOfTiles.at(position)->foodCost;
    }
    if (getResourceType(position)=="Gold") {
        return listOfTiles.at(position)->goldCost;
    }
    return 0;
}
}