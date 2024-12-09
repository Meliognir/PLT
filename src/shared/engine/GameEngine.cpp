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

    game->request(); // Appelle le comportement de GameConfigState pour initialiser les joueurs

    // Transition vers l'état "Playing"
    //game->request2(); // Change l'état pour PlayingState

    // Configure les paramètres de la carte et des joueurs
    //game->request1();
}

// La boucle while doit être déplacée vers le client
void engine::GameEngine::steps() {

    while(!game->checkGameEndCondition()) {
        std::string wait;
       // switch (state) :
        game->request();
        std::cout << "Continue playing ?" << std::endl;
        std::cin >> wait;

    }
   /* const std::vector<state::Player *> &playingPlayers = game->getPlayerList();
    state::Player* currentPlayer;
    int playerCount = playingPlayers.size();
    int startingPlayerIndex = 0;
    int turn = 0;

    //client::InputHandler inputHandler;

    while (!game->checkGameEndCondition()) {
        //-------------Captain + Round------------
        std::cout << "Starting a new round in the Playerlist." << std::endl;
        turn++; 
        game->setTurn(turn);
        currentPlayer = playingPlayers.at(startingPlayerIndex);
        game->setCaptainIndex(startingPlayerIndex);
        
        //-------------Day and night Dices------------
        //inputHandler.displayMessage("Player " + std::to_string(currentPlayer->getPlayerId()) + " rolls the dice.");
        std::cout << "Player " << currentPlayer->getPlayerId() << "rolls the dice." << std::endl;
        std::array<int, 2> dice = DiceManager::rollDice();
        int die1 = dice[0];
        int die2 = dice[1];*/
}





        /*//changement d'état choix de dé
        //bool dayFirst = client::InputHandler::chooseTimeDice(die1, die2);

        std::array<int, 2> dayNightDice = DiceManager::assignDayAndNightDice(die1, die2, dayFirst);
        int dayDie = dayNightDice[0];  
        int nightDie = dayNightDice[1];

        game->dayDie = dayDie;  
        game->nightDie = nightDie;
        std::cout <<"The day die is " << std::to_string(dayDie) << " and the night die is " << std::to_string(nightDie) << "."<<std::endl;

        //-------------Every Player choose 1 Card in their own cardDeck------------
        for (int i = 0; i < playerCount; i++) {
            game->setActivePlayerIndex((startingPlayerIndex + i) % playerCount);
            game->setActivePlayer(playingPlayers.at(activePlayerIndex));
            std::cout << "Player " << game->getActivePlayer()->getPlayerId() << "'s turn. Choose your card wisely." << std::endl;
            //on change d'état vers un choix de carte
            //chooseCardFromHand(activePlayer->getHandCards());
        }

        //-------------Every Player execute day and night Actions of their chosen card------------
        for (int i = 0; i < playerCount; i++) {
            game->setActivePlayerIndex((startingPlayerIndex + i) % playerCount);
            game->setActivePlayer(playingPlayers.at(activePlayerIndex));
            std::cout << "Player " << game->getActivePlayer()->getPlayerId() << "'s turn. Execute your Action. Dew it." << std::endl;
            // add combat logic in Player.cpp
            game->getActivePlayer()->playTurn(playingPlayers);
        }

        startingPlayerIndex = (startingPlayerIndex + 1) % playerCount;
    }
}*/