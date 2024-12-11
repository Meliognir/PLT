#include "ChooseNbOfPlayers.h"
#include <string>
#include "../../src/shared/state.h"


engine::ChooseNbOfPlayers::ChooseNbOfPlayers(int numberOfPlayers) : numberOfPlayers(numberOfPlayers){
}

void const engine::ChooseNbOfPlayers::launchCommand (state::Game * GamePtr){
  std::string playerName;
  std::vector<state::Player*> players;
  for (int i =0; i<numberOfPlayers; i++){
      playerName="player " + i ;
      state::Player * player=new state::Player(i,playerName);
      players.push_back(player);
  }
  GamePtr->setPlayerList(players);

}