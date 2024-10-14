#include "State.h"
#include <iostream>
namespace state {

  State::~State() {}
  
  void State::setContext(Game *game) {
    this->game = game; 
  }
}