#include "GameEngine.h"
#include "../state.h"
#include "../state/GameOverState.h"
#include "../../client/client.h"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <utility>

engine::GameEngine::GameEngine(state::State *state){
    game = new state::Game(state);
}

void engine::GameEngine::initializeGame(int playerCount){

    game->request(); // Appelle GameConfigState pour initialiser les joueurs

}

void engine::GameEngine::steps() {

    //while(!game->checkGameEndCondition()) {
        std::string wait;
        // switch (state) :
        game->request();
        std::cout << "Continue playing ?" << std::endl;
        std::cin >> wait;

    //}
}
/* 
OK    const std::vector<state::Player *> &playingPlayers = game->getPlayerList();
    state::Player* currentPlayer;
OK    int playerCount = playingPlayers.size();
OK    int CaptainIndex = 0;
OK    int turn = 0;

    while (!game->checkGameEndCondition()) {
        //-------------Captain + Round------------
        std::cout << "Starting a new round in the Playerlist." << std::endl;
OK        turn++; 
OK        game->setTurn(turn);
OK        currentPlayer = playingPlayers.at(CaptainIndex);
OK        game->setCaptainIndex(CaptainIndex);
        
        //-------------Day and night Dices------------

        //-------------Every Player choose 1 Card in their own cardDeck------------
        for (int i = 0; i < playerCount; i++) {
            game->setActivePlayerIndex((CaptainIndex + i) % playerCount);
            game->setActivePlayer(playingPlayers.at(activePlayerIndex));
            std::cout << "Player " << game->getActivePlayer()->getPlayerId() << "'s turn. Choose your card wisely." << std::endl;
            //on change d'état vers un choix de carte
            //chooseCardFromHand(activePlayer->getHandCards());
        }

        //-------------Every Player execute day and night Actions of their chosen card------------
        for (int i = 0; i < playerCount; i++) {
OK            game->setActivePlayerIndex((CaptainIndex + i) % playerCount);
OK            game->setActivePlayer(playingPlayers.at(activePlayerIndex));
            std::cout << "Player " << game->getActivePlayer()->getPlayerId() << "'s turn. Execute your Action. Dew it." << std::endl;
            // add combat logic in Player.cpp
            game->getActivePlayer()->playTurn(playingPlayers);
        }

OK        CaptainIndex = (CaptainIndex + 1) % playerCount;
    }
}*/