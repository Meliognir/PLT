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
}