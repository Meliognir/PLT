#include "ActionCard.h"
#include "Game.h"
#include "Player.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <random>

#define DAY true
#define NIGHT false

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ADD_FOOD 2
#define ADD_GOLD 3
#define ADD_CANONS 4

namespace state{
bool Game::time = true;
int Game::dayDie = 0;
int Game::nightDie = 0;
Map* Game::map;
std::vector<ActionCard *> Game::collectionOfCards = {};

void Game::gameTurn(int time){

}

Game::Game(State *state) {
    this->transitionTo(state);

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

    try {
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
            uint8_t dayAction, nightAction;
            uint8_t* actions[2] = {&dayAction, &nightAction};

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
            collectionOfCards.push_back(new ActionCard(*actions[0], *actions[1]));
            /*
            printf("%u\n", collectionOfCards.at(0)->getDayAction());
            printf("%u\n", collectionOfCards.at(0)->getNightAction());*/


        }


        file.close();
    }catch (std::exception e){
        std::cerr << "Le fichier de carte n'a pas été ouvert correctement..." << std::endl;
    }

}


void Game::transitionTo(State *state){
    if (this->state != nullptr){
        delete this->state;
    }
    this->state = state;
    this->state->setContext(this);
}

void Game::request(){
    this->state->handle();
}

int Game::getTurn() const
{
    return this->turn;
}

void Game::setTurn(int turn)
{
    this->turn = turn;
}

const std::vector<Player *> &Game::getPlayerList() const{
    return this->playerList;
}

void Game::setPlayerList(const std::vector<Player *> &playerList){
    this->playerList = playerList;
}

int Game::getCaptainIndex() const{
    return this->captainIndex;
}

void Game::setCaptainIndex(int captainIndex){
    this->captainIndex = captainIndex;
}

void Game::displayState()
{
    // Ecran principal avec la map et la position des joueurs
    int mapSize = map->getSize();
    printf("Affichage de la map :\n");
    std::cout<<"Tuile N°0 : Ceci est la tuile de départ, il y a rien à payer ici." << std::endl;
    for (int i = 1; i < mapSize; i++){
        std::cout<< "Tuile N°" << i << " contient : ";
        if(map->getResourceCost(i)>0) {
            std::cout<<"Il y a "<<map->getResourceCost(i)<< " " <<map->getResourceType(i)<< " à payer sur cette tuile." << std::endl;
        }
        if(map->getResourceType(i)=="Treasure") {
            std::cout<<"Il y a un "<<map->getResourceType(i)<< " à gagner sur cette tuile." << std::endl;
        }

    }

    // Affichage des boatholds, trésors, cartes
    for(Player * player : getPlayerList()){
        int i=0;
        std::cout<< "Cales de "<< player->getName()<<" :" << std::endl;
        for (BoatHold *bh:player->getBoatHolds()) {
            std::cout<< "BoatHold N°" << i << " : " ;
            bh->showContent();
            i++;
        }
        std::cout<< "Trésors de "<< player->getName()<<" :" << std::endl;
        //à compléter
        int j=1;
        std::cout<<"Cartes de "<< player->getName()<<" :" << std::endl;
        for (int cardIndex : player->getHandCards()) {
            std::cout<< "Card N°" << j << " : " ;
            std::string dayAction;
            std::string nightAction;
            if(collectionOfCards.at(cardIndex)->getDayAction()==0) {
                dayAction="move forward";
            }
            if(collectionOfCards.at(cardIndex)->getDayAction()==1) {
                dayAction="move backward";
            }
            if(collectionOfCards.at(cardIndex)->getDayAction()==2) {
                dayAction="food";
            }
            if(collectionOfCards.at(cardIndex)->getDayAction()==3) {
                dayAction="gold";
            }
            if(collectionOfCards.at(cardIndex)->getDayAction()==4) {
                dayAction="canon";
            }
            if(collectionOfCards.at(cardIndex)->getNightAction()==0) {
                nightAction="move forward";
            }
            if(collectionOfCards.at(cardIndex)->getNightAction()==1) {
                nightAction="move backward";
            }
            if(collectionOfCards.at(cardIndex)->getNightAction()==2) {
                nightAction="food";
            }
            if(collectionOfCards.at(cardIndex)->getNightAction()==3) {
                nightAction="gold";
            }
            if(collectionOfCards.at(cardIndex)->getNightAction()==4) {
                nightAction="canon";
            }
            std::cout<<"Action du jour : "<< dayAction <<", ";
            std::cout <<"Action de la nuit : "<<nightAction<<"."<< std::endl;
            j++;
        }
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

//unused
void Game::rollDice(){
    dayDie = rand() % 6 + 1;
    nightDie = rand() % 6 + 1;
}

//unused
void movePlayer(state::Player * player, int direction, int value){
    //ResourceManager resourceManager2;
    //state::Tile * currentTile = state::Game::map->listOfTiles.at(player->getPosition() % map.getSize());
    int nextPosition = player->getPosition()+value*direction;
    int nextPath = player->getPath();
    /*
    if (Map->path1.at(nextPosition % map.getSize()).isForking()){
        nextPath = InputHandler::pick_a_path();
    }*/
    player->setPosition(nextPosition);
    player->setPath(nextPath);
}

void Game::setAttackingPlayer(Player *player){
    attackingPlayer=player;
}

void Game::setDefendingPlayer(Player *player){
    defendingPlayer=player;
}

Player *Game::getAttackingPlayer(){
    return attackingPlayer;
}

Player *Game::getDefendingPlayer(){
    return defendingPlayer;
}

Player *Game::getCombatWinner(){
    return combatWinner;
}

void Game::setCombatWinner(Player *player){
    combatWinner=player;
}

Map *Game::getMap(){
    return map;
}

void Game::setMap(Map *newMap){
    map = newMap;
}

void Game::setMapReady(bool ready){
    isMapReady = ready;
}

bool Game::isMapInitialized(){
    return isMapReady;
}

Player *Game::getCombatLoser()
{
    return this->combatLoser;
}

void Game::setCombatLoser(Player *player)
{
    this->combatLoser = player;
}

int Game::getActivePlayerIndex() const{
    return activePlayerIndex;
}

Player* Game::getActivePlayer(){
    return activePlayer;
}

void Game::setActivePlayerIndex(int index){
    activePlayerIndex = index;
}

bool Game::getGameOver() const
{
    return this->gameOver;
}

void Game::setGameOver(bool gameOver)
{
    this->gameOver = gameOver;
}

void Game::setActivePlayer(Player *player){
    activePlayer = player;
}

Game::~Game(){
    /*
    for (Tile * tile : map){
        delete tile;
    }*/
    //delete map;
    delete state;
    for(Player* player : playerList){
        delete player;
    }
    playerList.clear();
    for (auto card : collectionOfCards) {
        delete card;
    }
}


}