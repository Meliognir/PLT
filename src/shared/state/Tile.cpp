//
// Created by trias on 14/10/24.
//
#include "Tile.h"
#include <string>

namespace state {
Tile::Tile(int cost, std::string resource, int nbPlayer) :
tileCost(cost),tileResourceType(resource),nbPlayer(nbPlayer){

}

state::Tile::~Tile()=default;

}