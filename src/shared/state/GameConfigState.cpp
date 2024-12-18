#include "GameConfigState.h"
#include "Game.h"
#include "state.h"
#include "Player.h"
#include "CaptainDiceState.h"
#include "Gold.h"
#include "Food.h"
#include "../../client/client/InputHandler.h"
#include "../engine/ResourceManager.h"
#include <iostream>
#include <vector>
#include <memory>
#include <limits> 

#define GAME_CONFIG_STATE     0

#define TREASURE 0
#define GOLD 1
#define FOOD 2

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
namespace state {

  void GameConfigState::handle() {
    
    game->setCaptainIndex(0);
    game->setActivePlayerIndex(0); // set to 0 here and in CardActionState
    
    std::cout <<"Transitioning to CaptainDice state..."<< std::endl;
    game->transitionTo(new CaptainDiceState);

  }

  int GameConfigState::getStateId (){
    return GAME_CONFIG_STATE;
  }
  
  GameConfigState::~GameConfigState() {
    std::cout <<"GameConfig destructor called"<< std::endl;
  }

} 
