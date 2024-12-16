#include "ChooseMapSize.h"


engine::ChooseMapSize::ChooseMapSize(int size) : size(size){

}

void const engine::ChooseMapSize::launchCommand (state::Game * GamePtr){
    GamePtr->map->setSize(size);
}

engine::ChooseMapSize::~ChooseMapSize(){}