#include "ActionCard.h"
#include "Game.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>

#define DAY true
#define NIGHT false

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ADD_FOOD 2
#define ADD_GOLD 3
#define ADD_CANONS 4

namespace state{

int Game::dayDie = 0;
int Game::nightDie = 0;
bool Game::time = true;
std::vector<ActionCard *> Game::collectionOfCards = {};

void Game::gameTurn(int time){

}

Game::Game(State *state, Map *map)
{
    this->transitionTo(state);
    this->map = map;

    // Example of a collectionOfCards
    // collectionOfCards = {
    //     new ActionCard(MOVE_FORWARD, MOVE_FORWARD),
    //     new ActionCard(MOVE_BACKWARD, MOVE_FORWARD),
    //     new ActionCard(MOVE_FORWARD, MOVE_BACKWARD),
    //     new ActionCard(ADD_GOLD, ADD_GOLD),
    //     new ActionCard(ADD_FOOD, ADD_GOLD),
    //     new ActionCard(ADD_GOLD, ADD_FOOD),
    //     new ActionCard(ADD_GOLD, ADD_CANONS),
    //     new ActionCard(ADD_CANONS, ADD_GOLD),
    //     new ActionCard(ADD_FOOD, ADD_CANONS),
    //     new ActionCard(ADD_CANONS, ADD_FOOD)
    // };

    std::ifstream file("../src/boardGameData/officialActionCards.csv"); // "../../src/boardGameData/cards.csv"
    std::string line;
    
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier cards.csv." << std::endl;
        return;
    }

    // Ignore la première ligne (les en-têtes)
    std::getline(file, line);
    
    // Lire chaque ligne et créer une ActionCard
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string readAction;
        int dayAction, nightAction;
        int* actions[2] = {&dayAction, &nightAction}; 

        for (int i= 0; i<2; i++){
            // read csv file
            std::getline(ss, readAction, ',');
            // fill the dayAction or nightAction with the read value
            if (readAction == "forward"){
                *actions[i] = MOVE_FORWARD;
            }
            if (readAction == "backward"){
                *actions[i] = MOVE_BACKWARD;
            }
            if (readAction == "food"){
                *actions[i] = ADD_FOOD;
            }
            if (readAction == "gold"){
                *actions[i] = ADD_GOLD;
            }
            if (readAction == "canons"){
                *actions[i] = ADD_CANONS;
            }
        }
        // create ActionCard based on the read actions
        collectionOfCards.push_back(new ActionCard(dayAction, nightAction));
    }
    file.close();
}

Game::~Game(){
    delete map;
    delete state;
    for(Player* player : playerList){
        delete player;
    }
    playerList.clear();
    for (auto card : collectionOfCards) {
        delete card;
    }
}

void Game::transitionTo(State *state){
    if (this->state != nullptr){
        delete this->state;
    }
    this->state = state;
    this->state->setContext(this);
}

void Game::request1(){
    this->state->handle1();
}

void Game::request2(){
    this->state->handle2();
}
void Game::setTurn(int turn){
}

const std::vector<Player *> &Game::getPlayerList() const{
    return this->playerList;
}

void Game::setPlayerList(const std::vector<Player *> &playerList){
    this->playerList=playerList;
}

void Game::setCaptainIndex(int captainIndex){
}

void Game::displayState()
{
    // Ecran principal avec la map et la position des joueurs
    int mapSize = map->getSize();
    printf("Affichage de la map :\n");
    for (int i = 0; i < mapSize; i++){
        printf("Affichage de la tuile i\n");
    }

    // Ecran dédié aux états actuels des joueurs et les ressources dans leur cale
    int numberOfPlayers = getPlayerList().size();
    for (int i = 0; i < numberOfPlayers; i++){
        printf("Affichage des informations du i-ème joueur\n");
    }
}

bool Game::checkGameEndCondition(){
    for (Player* player : playerList) {
        if(player->getPosition() >= map->getSize()){
            return true;
        }
    }
    return false;
}

}