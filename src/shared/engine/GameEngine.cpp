#include "GameEngine.h"
#include "../state.h"
#include "../../client/client.h"
#include "DiceManager.h"
#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <utility>

engine::GameEngine::GameEngine(state::State *state, state::Map *map)
{
     if (map == nullptr) {
        map = new state::Map(10); // Taille par défaut, si nécessaire
    }

    // Initialisation correcte de game avec state et map
    game = new state::Game(state, map);
}

void engine::GameEngine::runGameLoop()
{
    const std::vector<state::Player *> &playingPlayers = game->getPlayerList();
    state::Player* currentPlayer;
    state::Player* activePlayer;
    int playerCount = playingPlayers.size();
    int startingPlayerIndex = 0;
    int activePlayerIndex = 0;
    int turn = 0;

    client::InputHandler inputHandler;

    while (!game->checkGameEndCondition()) {
        //-------------Captain + Round------------
        std::cout << "Starting a new round in the Playerlist." << std::endl;
        turn++; 
        game->setTurn(turn);
        currentPlayer = playingPlayers[startingPlayerIndex];
        game->setCaptainIndex(startingPlayerIndex);
        
        //-------------Day and night Dices------------
        inputHandler.displayMessage("Player " + std::to_string(currentPlayer->getPlayerId()) + " rolls the dice.");
        std::array<int, 2> dice = engine::DiceManager::rollDice();
        int die1 = dice[0];
        int die2 = dice[1];

        bool dayFirst = client::InputHandler::chooseTimeDice(die1, die2);

        std::array<int, 2> dayNightDice = engine::DiceManager::assignDayAndNightDice(die1, die2, dayFirst);
        int dayDie = dayNightDice[0];  
        int nightDie = dayNightDice[1];

        game->dayDie = dayDie;  
        game->nightDie = nightDie;
        inputHandler.displayMessage("The day die is " + std::to_string(dayDie) + " and the night die is " + std::to_string(nightDie) + ".");

        //-------------Every Player choose 1 Card in their own cardDeck------------
        for (int i = 0; i < playerCount; i++) {
            activePlayerIndex = (startingPlayerIndex + i) % playerCount;
            activePlayer = playingPlayers[activePlayerIndex];
            std::cout << "Player " << activePlayer->getPlayerId() << "'s turn. Choose your card wisely." << std::endl;
            activePlayer->chooseCard();
        }

        //-------------Every Player execute day and night Actions of their chosen card------------
        for (int i = 0; i < playerCount; i++) {
            activePlayerIndex = (startingPlayerIndex + i) % playerCount;
            activePlayer = playingPlayers[activePlayerIndex];
            std::cout << "Player " << activePlayer->getPlayerId() << "'s turn. Execute your Action. Dew it." << std::endl;
            // add combat logic in Player.cpp
            activePlayer->playTurn();
        }

        startingPlayerIndex = (startingPlayerIndex + 1) % playerCount;
    }
}