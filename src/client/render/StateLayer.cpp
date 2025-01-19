#include "StateLayer.h"
#include "Renderer.h"
#include "state.h"
#include "client.h"
#include "client/InputHandler.h"
#include "engine.h"
#include <iostream>
#include <thread>

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

render::StateLayer::StateLayer(state::Game * game, Renderer * renderer, HUD * hud, UserInputListener* userInputListener, sf::RenderWindow * window) : game(game), renderer(renderer), instHUD(hud), userInputListener(userInputListener), window(window){
}

void render::StateLayer::update(){
    engine::GameEngine * gameEngineInstance = engine::GameEngine::getInstance(nullptr);
    setCurrentStateID(gameEngineInstance->game->state->getStateId());
}

void render::StateLayer::setCurrentStateID(int StateID){
    this->currentStateID=StateID;
}

void render::StateLayer::runRenderLoop(client::Client* client) {
    userInputListener->userInput = "";
    bool animationWasPlayed = false;
    renderer->renderBackground(*window);
    instHUD->welcomeMessage(*window);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));


    while (window->isOpen() && client->running) {
        window->clear();

        // Interpret mouse clics and key inputs to read user input or close the window
        userInputListener->readInput(window, client->inputHandler);

        switch(currentStateID){
            case GAME_CONFIG_STATE:{
                //animationWasPlayed = false;
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
                                if (!animationWasPlayed){
                                renderer->renderFinalAnimation(*window, game->getPlayerList(), *game->map);
                                instHUD->displayResults(*window, game->getPlayerList(), game->map->getSize());
                                animationWasPlayed = true;
                                }
                }
                break;
            }
            case CAPTAIN_DICE_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, client::Client::die1, client::Client::die2);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                int captainIndex = game->getCaptainIndex();
                state::Player * captain = game->getPlayerList().at(captainIndex);
                std::vector<int> playerHand = captain->getHandCards();
                renderer->renderHand(*window, playerHand);
                renderer->renderBoatholds(*window, captain, 0);
                instHUD->askDayDice(*window, client::Client::die1, client::Client::die2, captain->getName());
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
                state::Player * currentPlayer = game->getActivePlayer();
                std::vector<int> playerHand = currentPlayer->getHandCards();
                renderer->renderBoatholds(*window, game->getActivePlayer(), 0);
                renderer->renderHand(*window, playerHand);
                instHUD->askCard(*window, currentPlayer->getName());
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
                renderer->renderBoatholds(*window, game->getActivePlayer(), 0);
                break;}
            case RESOURCE_HANDLING_STATE: {
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                state::Player * currentPlayer = game->getActivePlayer();
                renderer->renderBoatholds(*window, currentPlayer, 0);
                
                if (client::Client::gettingResources){
                    instHUD->askPlaceResource(*window, currentPlayer->getName(), currentPlayer->getBoatHolds().size(), client::Client::currentDie, client::Client::resTypeToAdd);
                }
                if(currentPlayer->getHasToPay() && currentPlayer->getHasMoved()){
                    instHUD->askBoatholdToPay(*window, currentPlayer->getName(), currentPlayer->getBoatHolds().size(), currentPlayer->getAmountToPay(),client::Client::resTypeToPay);
                }
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
                state::Player * currentPlayer = game->getActivePlayer();
                renderer->renderBoatholds(*window, game->getActivePlayer(), 0);
                instHUD->askOpponent(*window, currentPlayer->getName(), currentPlayer->getOpponentsList());
                break;
            }
            case COMBAT_ATTACKING_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getAttackingPlayer()) {
                    break;
                }
                int playerNbCanons = 0;
                for (state::BoatHold *bh : game->getAttackingPlayer()->getBoatHolds()){
                    if (bh->hasResourceType("Canon")) {
                        playerNbCanons += bh->getQuantity();
                    }
                }
                renderer->renderBoatholds(*window, game->getAttackingPlayer(), 0);
                instHUD->askCanonNb(*window, game->getAttackingPlayer()->getName(), playerNbCanons);
                break;
            }
            case COMBAT_DEFENDING_STATE:{
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getDefendingPlayer()) {
                    break;
                }
                int playerNbCanons = 0;
                for (state::BoatHold *bh : game->getDefendingPlayer()->getBoatHolds()){
                    if (bh->hasResourceType("Canon")) {
                        playerNbCanons += bh->getQuantity();
                    }
                }
                renderer->renderBoatholds(*window, game->getDefendingPlayer(), 0);
                instHUD->askCanonNb(*window, game->getDefendingPlayer()->getName(), playerNbCanons);
                break;
            }
            case STEAL_RESOURCE_STATE:{ //TODO : instHUD->affichagedetextecaleavoler et instHUD->affichagedetextecaleadeposer
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderDice(*window, state::Game::dayDie, state::Game::nightDie);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);
                if (!game->getActivePlayer()) {
                    break;
                }
                renderer->renderBoatholds(*window, game->getCombatLoser(), 0);
                renderer->renderBoatholds(*window, game->getCombatWinner(), 100);
                break;
            }
            case GAME_OVER_STATE:{
                /*
                renderer->renderBackground(*window);
                renderer->renderMap(*window, *game->map);
                renderer->renderPlayers(*window, game->getPlayerList(), *game->map);*/
                //only show the animation once :
                if (!animationWasPlayed){
                    renderer->renderFinalAnimation(*window, game->getPlayerList(), *game->map);
                    instHUD->displayResults(*window, game->getPlayerList(), game->map->getSize());
                    animationWasPlayed = true;
                }
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
        userInputListener->echo(window);//show their current input to the user
        window->display();
    }
}

void render::StateLayer::setWindow(sf::RenderWindow *window){
    this->window=window;
}
