#include "ActionCard.h"
#include "Game.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace state{

void Game::gameTurn(int time){

}

Game::Game(State *state, Map *map)
{
    this->transitionTo(state);
    this->map = map;

    // collectionOfCards = {
    //     new ActionCard(0, "forward", "forward"),
    //     new ActionCard(1, "backward", "forward"),
    //     new ActionCard(2, "forward", "backward"),
    //     new ActionCard(3, "gold", "gold"),
    //     new ActionCard(4, "food", "gold"),
    //     new ActionCard(5, "gold", "food"),
    //     new ActionCard(6, "gold", "canons"),
    //     new ActionCard(7, "canons", "gold"),
    //     new ActionCard(8, "food", "canons"),
    //     new ActionCard(9, "canons", "food")
    // };

    std::ifstream file("src/boardGameData/cards.csv"); // "../../src/boardGameData/cards.csv"
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
        int cardID;
        std::string dayAction, nightAction;

        // Lire les valeurs du fichier CSV
        ss >> cardID;
        ss.ignore(1, ','); // Ignorer la virgule
        std::getline(ss, dayAction, ',');
        std::getline(ss, nightAction);

        // Créer l'ActionCard avec les actions lues
        collectionOfCards.push_back(new ActionCard(cardID, dayAction, nightAction));
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
}

}