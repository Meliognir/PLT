#include "StateLayer.h"
#include "Renderer.h"
#include "state.h"
#include "client.h"
#include "engine.h"
#include <iostream>

#define GAME_CONFIG_STATE 0
#define CAPTAIN_DICE_STATE 1
#define CARD_CHOICE_STATE 2
#define CARD_ACTION_STATE 3
#define RESOURCE_HANDLING_STATE 4
#define OPPONENT_CHOICE_STATE 5
#define COMBAT_ATTACKING_STATE 6
#define COMBAT_DEFENDING_STATE 7
#define STEAL_RESOURCE_STATE 8
#define GAME_OVER_STATE 9

render::StateLayer::StateLayer(Renderer * renderer, state::Game * game, sf::RenderWindow * window) : game(game), renderer(renderer), window(window){
}

void render::StateLayer::update(){
    engine::GameEngine * gameEngineInstance = engine::GameEngine::getInstance(nullptr);
    setCurrentStateID(gameEngineInstance->game->state->getStateId());
}

void render::StateLayer::setCurrentStateID(int StateID){
    this->currentStateID=StateID;
}

void render::StateLayer::runRenderLoop(client::Client* client) {
    while (window->isOpen() && client->running) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->clear();
        // Rendu de la carte
        switch(currentStateID){
            case GAME_CONFIG_STATE:
            break;
            case CAPTAIN_DICE_STATE:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
            break;
            }
            
            case CARD_CHOICE_STATE:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                std::vector<int> playerHand = game->getActivePlayer()->getHandCards();
                renderer->renderHand(*window, playerHand);
                break;
            }

            case CARD_ACTION_STATE: {
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;}
            case RESOURCE_HANDLING_STATE: {
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getActivePlayer());
                break;
            }
            case OPPONENT_CHOICE_STATE:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
            case COMBAT_ATTACKING_STATE:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
            case COMBAT_DEFENDING_STATE:
            {
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
            case STEAL_RESOURCE_STATE:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
            case GAME_OVER_STATE:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
            default:{
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
        }
        window->display();
    }
}

void render::StateLayer::setWindow(sf::RenderWindow *window){
    this->window=window;
}
