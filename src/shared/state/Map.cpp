#include "Map.h"

namespace state {

Map::~Map(){
}

bool Map::hasFork(int position, int direction)
{
    return false;
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
   return listOfTiles.at(position)->tileResourceType;
}

int Map::getResourceCost (int position) {
    return listOfTiles.at(position)->tileCost;
}
}