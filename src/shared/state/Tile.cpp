//
// Created by trias on 14/10/24.
//
#include "Tile.h"

state::Tile::Tile(int foodCost, int goldCost, bool treasure, int nbPlayer) :
foodCost(foodCost),goldCost(goldCost),treasure(treasure),nbPlayer(nbPlayer){

}

state::Tile::~Tile()=default;