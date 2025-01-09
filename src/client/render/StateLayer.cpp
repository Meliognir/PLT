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

render::StateLayer::StateLayer(Renderer * renderer, HUD * hud, state::Game * game, sf::RenderWindow * window) : game(game), instHUD(hud), renderer(renderer), window(window){
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
        switch(currentStateID){
            case GAME_CONFIG_STATE:{
                renderer->renderBackground(*window); 
                if (client::Client::modeChosen && !client::Client::nbPlayerChosen){
                    instHUD->askNumberofPlayers(*window);
                }
                else if (!client::Client::modeChosen){
                    instHUD->askGamemode(*window);
                }
                if (!game->getActivePlayer()) {
                    break;
                }
                state::Player * currentPlayer = game->getActivePlayer();
                if (!client::Client::allPlayerSet){
                    if (client::Client::nbPlayerChosen && !client::Client::isPlayerTypeChosen){
                        instHUD->askIsPlayerAI(*window, currentPlayer->getPlayerId()+1);
                    }
                    if (client::Client::isPlayerTypeChosen){
                        if (!client::Client::isPlayerAI){
                            instHUD->askPlayerName(*window, currentPlayer->getPlayerId()+1);
                        }
                        if (client::Client::isPlayerAI) {
                            instHUD->askAIDifficulty(*window);
                        }  
                    }
                     
                }
                else {
                    instHUD->askMapSize(*window);
                }
                break;
            }
            case CAPTAIN_DICE_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, client::Client::die1, client::Client::die2);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                instHUD->askDayDice(*window, client::Client::die1, client::Client::die2);
                break;
            }
            
            case CARD_CHOICE_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                std::vector<int> playerHand = game->getActivePlayer()->getHandCards();
                renderer->renderHand(*window, playerHand);
                instHUD->askCard(*window);
                break;
            }

            case CARD_ACTION_STATE: {
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getActivePlayer());
                break;}
            case RESOURCE_HANDLING_STATE: {
                renderer->renderBackground(*window);
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
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getActivePlayer());
                break;
            }
            case COMBAT_ATTACKING_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getActivePlayer());
                break;
            }
            case COMBAT_DEFENDING_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getActivePlayer());
                break;
            }
            case STEAL_RESOURCE_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getActivePlayer());
                break;
            }
            case GAME_OVER_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                break;
            }
            default:{
                renderer->renderBackground(*window);
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
