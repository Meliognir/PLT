#include "Map.h"
#include <iostream>
#include <algorithm>

template <typename T>
constexpr const T& clamp(const T& value, const T& lower, const T& upper) {
    return (value < lower) ? lower : (value > upper ? upper : value);
}

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
    int actualPosition = position;
    if (actualPosition < 0){
        actualPosition = getSize() - (-actualPosition)%getSize();
    }
    else if (actualPosition > getSize()-1){
        actualPosition = actualPosition%getSize();
    } 
    return listOfTiles.at(actualPosition)->tileResourceType;

}

int Map::getResourceCost (int position) {
    int actualPosition = position;
    if (actualPosition < 0){
        actualPosition = getSize() - (-actualPosition)%getSize();
    }
    else if (actualPosition > getSize()-1){
        actualPosition = actualPosition%getSize();
    }
    return listOfTiles.at(actualPosition)->tileCost;

}
}