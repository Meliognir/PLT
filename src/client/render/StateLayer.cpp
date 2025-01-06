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

void render::StateLayer::initSurfaces(state::State *state)
{
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
        if (game->map) {
            renderer->renderMap(*window, *game->map);
            renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
        }

        // Rendu des joueurs
        renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
        // Rendu des cartes (par exemple)
        std::vector<int> playerHand = {2, 5, 10}; // ID des cartes dans la main
        renderer->renderHand(*window, playerHand);
        window->display();
    }
}