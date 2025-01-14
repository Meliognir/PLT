#include "client.h"
#include "state.h"
#include "state/Player.h"
#include "../shared/engine.h"

#include <iostream>
#include <limits>
#include <bits/unique_ptr.h>
#include "Client.h"

// ---- Network includes --------
#include "../../server/server/NetworkClient.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
// ------------------------------

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

#define TREASURE 0

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ADD_FOOD 2
#define ADD_GOLD 3
#define ADD_CANONS 4

#define COMBATDIE 1

#define EXIT_GAME 0
#define LOCAL_MULTIPLAYER 1
#define ONLINE_MULTIPLAYER 2
//#define DUEL_GAME 3


template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


namespace client {
    bool Client::modeChosen = false;
    bool Client::nbPlayerChosen = false;
    bool Client::isPlayerTypeChosen = false;
    bool Client::isPlayerAI = false;
    bool Client::allPlayerSet = false;
    int Client::die1 = 0;
    int Client::die2 = 0;
    int Client::currentDie = 0;
    std::string Client::resTypeToAdd = "Null";
    std::string Client::resTypeToPay = "Null";
    bool Client::gettingResources = false;

    Client::Client()
    {
        // Instantiates a new Game context and runs concrete state GameConfigState
        state::State *gameState = new state::GameConfigState();
        gameEngine = engine::GameEngine::getInstance(gameState);
        gameInstance = gameEngine->game;
        InputHandler inputHandler;
    }

    int Client::launch(){
        // Playing Modes
        running=true;
        //renderer-> show the correct window
        int playingMode = 1;
        while(playingMode){
            playingMode = inputHandler.selectGameMode(); //Dans quel mode souhaitez-vous jouer ? (0 = exit, 1 = local, 2 = online, 3 = ia)
            modeChosen=true;
            switch (playingMode){                        //quel est le mode 3 ? c'est SINGLE_PLAYER ou IA ?
                case EXIT_GAME :
                    break;
                case LOCAL_MULTIPLAYER :
                    runLocalGame();
                    break;
                case ONLINE_MULTIPLAYER :
                    runOnlineGame();
                    break;
                /*
                case TWO_PLAYERS_MODE :
                    runDuelGame();
                    break;
                */

                default :
                    break;
            }
            //cliquer aux bons endroits pour choisir le mode de jeu souhaité
            std::cout << "We hope you enjoyed your game !" << std::endl;
            std::string waitConfirm;
        }
        running = false;
        return 0;

    }

    int Client::runLocalGame(){

        //important
        // est ce que notre client vole le rôle de GameEngine ?
        // il faut faire GameEngine->fcn() à chaque fois que l'on modifie la valeur d'une variable de game avec un "set" ou un "="

        int gameState;

        // Init every game loop variable
        int numberOfPlayers;
        int actionCounter;
        int activePlayerIndex;
        int captainIndex;
        int turn;
        bool chosenDice;
        state::Player* activePlayer;
        int chosenCardVal;
        state::ActionCard *actionCard;
        int chosenBoatholdId;
        std::string chosenBoatholdResType;
        int boatHoldCount;
        int remainToPay;
        int boatHoldQuantity;
        int actionType;
        bool validChosenBoathold;
        bool isNaked;
        bool isFull;
        bool hasFought;
        int nbOpponent;
        int chosenOpponentId;
        std::vector<state::Player *> opponentsList;
        state::Player* combatPlayer;
        int playerNbCanons;
        state::Player* winner;
        state::Player* loser;
        int winnerBoatholdId;

        // Get the mapManager for movement logic
        engine::MapManager* mapManager = new engine::MapManager();

        // Init every game loop command
        engine::AssignDice* assignDice;
        engine::ChooseCard* chooseCard;
        engine::AddToBoathold* addToBoathold;
        engine::ChoosePath* choosePath; //unused
        engine::ChooseOpponent* chooseOpponent;
        engine::RollDice* rollDice;
        engine::ChooseCanons* chooseCanons;
        engine::StealResource* stealResource;

        // Game loop State behavior
        int endloop = 0;
        std::string waitConfirm;
        std::cout << "Client now entering the game loop\r\n" << std::endl;
        while (!endloop){

            gameState = gameInstance->state->getStateId();

            switch (gameState){

                case GAME_CONFIG_STATE:
                    std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
                
                    localGameConfigInit();
                    mapManager->setMapPtr(gameInstance->getMap());
                    gameInstance->request();
                    break;


                case CAPTAIN_DICE_STATE:

                    // partie réseau

                    // client récupère int captainIndex = gameInstance->getCaptainIndex(); 
                    // et donne le captainIndex à l'InputHandler bool InputHandler::chooseTimeDice(int die1, int die2, Player* captainIndex){}
                    // ensuite chooseTimeDice() affiche le message pour le joueur capitaine
                    // std::cout << "Joueur " << captainIndex << ", choisissez le dé qui sera le dé du jour. L'autre sera le dé de la nuit. (1 ou 2)\n << "Dé 1 : " << die1 << " Dé 2 : " << die2 << std::endl;
                    
                    // en même temps chooseTimeDice() envoie un message aux joueurs non captain "veuillez attendre le choix de dé du captain"

                    std::cout << "Client now entering CAPTAIN_DICE_STATE\r\n" << std::endl;
                    srand(time(NULL));
                    hasFought = false;
                    captainIndex = gameInstance->getCaptainIndex();
                    turn = gameInstance->getTurn();
                    if(turn > 0){captainIndex = (captainIndex + 1) % numberOfPlayers;}
                    gameInstance->setCaptainIndex(captainIndex);
                    gameInstance->actionCounter = 0;
                    activePlayer = gameInstance->getPlayerList().at(captainIndex);
                    gameInstance->setTurn(turn + 1);
                    die1 = rand()%6+1;
                    die2 = rand()%6+1;
                    std::cout << "Capitaine " << gameInstance->getPlayerList().at(captainIndex)->getName() << " : choisissez vos dés ! \r\n" << std::endl;
                    if (activePlayer->get_AI()==nullptr){ //real player
                        chosenDice = inputHandler.chooseTimeDice(die1, die2);
                    }
                    else { // AI input
                        activePlayer->get_AI()->chooseTimeDice(die1, die2);
                    }
                    if (chosenDice == 1){assignDice = new engine::AssignDice(die1, die2);}
                    else{assignDice = new engine::AssignDice(die2, die1);}
                    assignDice->launchCommand(gameInstance);
                    delete assignDice;

                    //moves activeCard from handDeck to cardDeck
                    turn = gameInstance->getTurn();
                    if(turn > 1){
                        for(state::Player * pl : gameInstance->getPlayerList()){
                            pl->moveCardToDeck();
                            pl->moveCardToHand();
                        }
                    }

                    gameInstance->request();
                    break;


                case CARD_CHOICE_STATE:

                    std::cout << "Client now entering CARD_CHOICE_STATE\r\n" << std::endl;
                    std::cout << "Starting a new round in the Playerlist\r\n" << std::endl;
                    captainIndex = gameInstance->getCaptainIndex();
                    numberOfPlayers = gameInstance->getPlayerList().size();

                    // partie réseau

                    // l'InputHandler affiche un message personnalisé "joueur truc choisis tes cartes"
                    // la boucle for en dessous n'existera pas tout le monde choisit en même temps
                    // pas d'active player pour le choosecard

                    // Every Player choose 1 Card in their own cardDeck
                    for(int i = 0; i < numberOfPlayers; i++) {
                        activePlayerIndex = (captainIndex + i) % numberOfPlayers;
                        gameInstance->setActivePlayerIndex(activePlayerIndex);
                        gameInstance->setActivePlayer(gameInstance->getPlayerList().at(activePlayerIndex));
                        activePlayer = gameInstance->getActivePlayer();
                        std::cout << "player: " << activePlayer->getName() << " activePLayerIndex: "<< activePlayerIndex << " id: " << activePlayer->getPlayerId() << "'s turn. Choose your card wisely\r\n" << std::endl;
                        gameInstance->displayState();
                        // Pick a card
                        if (activePlayer->get_AI()==nullptr){ //real player
                            chosenCardVal = inputHandler.chooseCardFromHand(activePlayer->getHandCards());
                        }
                        else { // AI input
                            chosenCardVal = activePlayer->get_AI()->chooseCardFromHand(activePlayer->getHandCards());
                        }

                        //chosenCardVal = inputHandler.chooseCardFromHand(activePlayer->getHandCards()); //old code
                        chooseCard = new engine::ChooseCard(activePlayer, chosenCardVal);
                        chooseCard->launchCommand(gameInstance);
                        delete chooseCard;

                    }
                    activePlayerIndex = captainIndex;
                    gameInstance->setActivePlayerIndex(activePlayerIndex);
                    
                    gameInstance->request(); // from cardchoicestate to cardactionstate
                    break;


                case CARD_ACTION_STATE:
                    std::cout << "Client now entering CARD_ACTION_STATE\r\n" << std::endl;
                    actionCounter = gameInstance->actionCounter;

                    // partie réseau

                    // mettre les joueurs en attente avec un message "le joueur activePlayer exécute ses actions"

                    std::cout << "Action number " << actionCounter << "\r\n" << std::endl;
                    // 2 actions day, night, 1 no action
                    if(actionCounter > 0 && actionCounter%2 == 0){activePlayerIndex = (activePlayerIndex + 1) % numberOfPlayers;}
                    gameInstance->setActivePlayerIndex(activePlayerIndex);
                    activePlayer = gameInstance->getPlayerList().at(activePlayerIndex);
                    gameInstance->setActivePlayer(activePlayer);
                    std::cout << "player: " << activePlayer->getName() << " activePlayerIndex: "<< activePlayerIndex << " id: " << activePlayer->getPlayerId() << " Do your Action. Dew it.\r\n" << std::endl;                                

                    activePlayer->setMustFight(false);
                    activePlayer->setHasMoved(false);
                    activePlayer->setHasToPay(false);
                    gettingResources = false;


                    // logique de déplacement sans input
                    chosenCardVal = activePlayer->getActiveCard();
                    // checks if current action is a movement or a Resource, do we use resourceManager ?
                    actionCard = state::Game::collectionOfCards.at(chosenCardVal);
                    boatHoldCount = activePlayer->getBoatHolds().size();
                    if(actionCounter%2 == 0){ //day
                        std::cout << "actionCounter%2 == 0\r\n" << std::endl;
                        actionType = actionCard->getDayAction();
                        currentDie = gameInstance->dayDie;
                        std::cout << "getDayAction: " << actionType << ".\r\n" << std::endl;
                    }
                    if(actionCounter%2 == 1){ //night
                        std::cout << "actionCounter%2 == 1\r\n" << std::endl;
                        actionType = actionCard->getNightAction();
                        currentDie = gameInstance->nightDie;
                        std::cout << "getNightAction: " << actionType << ".\r\n" << std::endl;
                    }
                    switch (actionType)
                    {
                    case MOVE_FORWARD:
                        mapManager->movePlayer(activePlayer, 1, currentDie);
                        activePlayer->setHasMoved(true);
                        activePlayer->setHasToPay(true);
                        gettingResources = false;
                        break;
                    case MOVE_BACKWARD:
                        mapManager->movePlayer(activePlayer, -1, currentDie);
                        activePlayer->setHasMoved(true);
                        activePlayer->setHasToPay(true);
                        gettingResources = false;
                        break;
                    case ADD_FOOD:
                        resTypeToAdd = "Food";
                        activePlayer->setHasMoved(false);
                        activePlayer->setHasToPay(false);
                        gettingResources = true;
                        break;
                    case ADD_GOLD:
                        resTypeToAdd = "Gold";
                        activePlayer->setHasMoved(false);
                        activePlayer->setHasToPay(false);
                        gettingResources = true;
                        break;
                    case ADD_CANONS:
                        resTypeToAdd = "Canon";
                        activePlayer->setHasMoved(false);
                        activePlayer->setHasToPay(false);
                        gettingResources = true;
                        break;
                    default:
                        std::cout << "You have played your last turn and the game is ending soon. You cannot play your night action." << std::endl;
                        break;
                    }

                    std::cout << "player: " << activePlayer->getName() << " activePlayerIndex: " << activePlayerIndex << " id: " << activePlayer->getPlayerId() << " position: "<< activePlayer->getPosition() << "\r\n"<< std::endl;
                    
                    actionCounter += 1;
                    gameInstance->actionCounter = actionCounter;
                    
                    gameInstance->request(); // from cardactionstate to resourcehandlingstate, or captaindicestate, or gameoverstate (according to condition)
                    break;


                case RESOURCE_HANDLING_STATE:
                    std::cout << "Client now entering RESOURCE_HANDLING_STATE\r\n" << std::endl;

                    activePlayer = gameInstance->getActivePlayer();

                    // if the player didn't move :
                    if(gettingResources){
                        isFull = true;
                        auto boatHolds = activePlayer->getBoatHolds();
                        for (state::BoatHold *bh : boatHolds) {
                            isFull = isFull && bh->hasResourceType(resTypeToAdd);
                        }

                        if(isFull){
                            std::cout << "Player: "<< activePlayer->getName() << " was full and couldn't receive: " << currentDie << " " << resTypeToAdd << std::endl;
                        }
                        else {

                            std::cout << "Player: "<< activePlayer->getName() << " receives: " << currentDie << " " << resTypeToAdd << ", Please choose a BoatHold to store this Resource\n";
                            validChosenBoathold = false;
                            while(!validChosenBoathold){
                                // Pick a boat hold
                                if (activePlayer->get_AI()==nullptr){ //real player
                                    chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                                }
                                else { // AI input
                                    chosenBoatholdId = activePlayer->get_AI()->selectUserBoatHold(boatHoldCount);
                                }
                                chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                                if(chosenBoatholdResType != resTypeToAdd){
                                    validChosenBoathold = true;
                                }
                                else {
                                    std::cout << "Invalid Boathold Type. You must choose a Boathold without : " << resTypeToAdd << ".\n";
                                }
                            }
                            addToBoathold = new engine::AddToBoathold(activePlayerIndex, chosenBoatholdId, currentDie, resTypeToAdd);
                            addToBoathold->launchCommand(gameInstance);
                            delete addToBoathold;
                        }
                        gettingResources = false;
                    }

                    else{
                        if(activePlayer->getHasToPay()){// The player moved on a new tile and must pay something (or pay 0 and get a treasure), and he could trigger a fight
                            nbOpponent = 0;
                            std::vector<state::Player *> opponentsList = {};
     
                            //player's total resource quantity he can pay for resTypeToPay
                            int activePlayerPos = activePlayer->getPosition();
                            resTypeToPay = gameInstance->map->getResourceType(activePlayerPos);
                            remainToPay = gameInstance->map->getResourceCost(activePlayerPos);
                            activePlayer->setResTypeToPay(resTypeToPay);
                            activePlayer->setAmountToPay(remainToPay);
                            int quantityResource = 0;
                            for (state::BoatHold *bh : activePlayer->getBoatHolds()) {
                                if (bh->hasResourceType(resTypeToPay)) {
                                    quantityResource += bh->getQuantity();
                                }
                            }
                            std::cout <<"player: " << activePlayer->getName() << " has: " << quantityResource << " resourceToPayType: " << resTypeToPay << "\r\n"<< std::endl;
                            std::cout <<"the tile costs: " << remainToPay << " resourceToPayType: " << resTypeToPay << "\r\n"<< std::endl;

                            //player can't pay
                            while(quantityResource < remainToPay){
                                
                                std::cout <<"player: " << activePlayer->getName() << " is going BANKRUPT for this tile.\r\n"<< std::endl;

                                if (quantityResource > 0){
                                    boatHoldCount = activePlayer->getBoatHolds().size();
                                    resTypeToPay = activePlayer->getResTypeToPay();
                                    remainToPay = activePlayer->getAmountToPay();
                                    std::cout << "Player: "<< activePlayer->getName() << " has to pay: " << remainToPay << " " << resTypeToPay << ".\n";
                                    while (quantityResource > 0){
                                        auto boatHolds = activePlayer->getBoatHolds();
                                        // Pick a boat hold
                                        if (activePlayer->get_AI()==nullptr){ //real player
                                            chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                                        }
                                        else { // AI input
                                            chosenBoatholdId = activePlayer->get_AI()->selectUserBoatHold(boatHoldCount, resTypeToPay, activePlayer->getPlayerId());
                                        }
                                        chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                                        if(chosenBoatholdResType != resTypeToPay){
                                            std::cout << "Invalid Resource Type. You chose a Boathold with: " << chosenBoatholdResType << " Please choose a BoatHold with: " << resTypeToPay << ".\n";
                                        }
                                        else{
                                            state::BoatHold *bh = boatHolds.at(chosenBoatholdId);
                                            boatHoldQuantity = bh->getQuantity();
                                            activePlayer->removeFromBoatHold(chosenBoatholdId, boatHoldQuantity);
                                            quantityResource = quantityResource - boatHoldQuantity;
                                            std::cout << "There remain: " << quantityResource << " " << resTypeToPay << " to pay.\n";
                                        }
                                    }
                                }               

                                //player moves backward
                                mapManager->moveOneTileBack(activePlayer);

                                activePlayer->setHasMoved(true);

                                //player's total resource quantity he can pay for resTypeToPay
                                activePlayerPos = activePlayer->getPosition();
                                resTypeToPay = gameInstance->map->getResourceType(activePlayerPos);
                                activePlayer->setResTypeToPay(resTypeToPay);
                                remainToPay = gameInstance->map->getResourceCost(activePlayerPos);
                                activePlayer->setAmountToPay(remainToPay);
                                quantityResource = 0;
                                for (state::BoatHold *bh : activePlayer->getBoatHolds()) {
                                    if (bh->hasResourceType(resTypeToPay)) {
                                        quantityResource += bh->getQuantity();
                                    }
                                }
                                std::cout <<"player: " << activePlayer->getName() << " has: " << quantityResource << " resourceToPayType: " << resTypeToPay << "\r\n"<< std::endl;
                                std::cout <<"the tile costs: " << remainToPay << " resourceToPayType: " << resTypeToPay << "\r\n"<< std::endl;
                            }
                            
                            // recall what the player now has to pay
                            activePlayerPos = activePlayer->getPosition();
                            resTypeToPay = gameInstance->map->getResourceType(activePlayerPos);
                            remainToPay = gameInstance->map->getResourceCost(activePlayerPos);
                            activePlayer->setHasToPay(true);

                            if (hasFought){
                                hasFought = false;
                                activePlayer->setMustFight(false);
                                activePlayer->setHasToPay(true); //no enemy ? then it's time to pay your debt

                            }
                            else {

                                //checks activeplayer's opponent presence before paying anything
                                for (state::Player *player : gameInstance->getPlayerList()) {
                                    if (player->getPosition() == activePlayerPos && player->getPlayerId() != activePlayer->getPlayerId()) {
                                        nbOpponent += 1;
                                        opponentsList.push_back(player);
                                    }
                                }
                                activePlayer->setOpponentsList(opponentsList);
                                std::cout <<"there are: " << nbOpponent << " opponents on this tile\r\n"<< std::endl;
                                                
                                //duel only if there are players
                                if (nbOpponent <= 0 || gameInstance->getMap()->getResourceType(activePlayerPos) == "Port Royale") {
                                    std::cout <<"Pon atencion Thorfinn, no tienes enemigos\r\n"<< std::endl;
                                    activePlayer->setMustFight(false);
                                    activePlayer->setHasToPay(true); //no enemy ? then it's time to pay your debt
                                }
                                else{
                                    std::cout <<" and Player: " << activePlayer->getName() << " must fight before he can pay the cost of this tile\r\n"<< std::endl;
                                    activePlayer->setMustFight(true);
                                    activePlayer->setAmountToPay(remainToPay);
                                    activePlayer->setResTypeToPay(resTypeToPay);

                                    activePlayer->setHasToPay(false);
                                }
                            }
                        }

                        //player selects boatholds to pay the new tile
                        if(activePlayer->getHasToPay()){
                            boatHoldCount = activePlayer->getBoatHolds().size();
                            resTypeToPay = activePlayer->getResTypeToPay();
                            remainToPay = activePlayer->getAmountToPay();
                            std::cout << "Player: "<< activePlayer->getName() << " has to pay: " << remainToPay << " " << resTypeToPay << ".\n";
                            while (remainToPay > 0){
                                auto boatHolds = activePlayer->getBoatHolds();
                                // Pick a boat hold
                                if (activePlayer->get_AI()==nullptr){ //real player
                                    chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                                }
                                else { // AI input
                                    chosenBoatholdId = activePlayer->get_AI()->selectUserBoatHold(boatHoldCount, resTypeToPay, activePlayer->getPlayerId());
                                }
                                chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                                if(chosenBoatholdResType != resTypeToPay){
                                    std::cout << "Invalid Resource Type. You chose a Boathold with: " << chosenBoatholdResType << " Please choose a BoatHold with: " << resTypeToPay << ".\n";
                                }
                                else{
                                    state::BoatHold *bh = boatHolds.at(chosenBoatholdId);
                                    boatHoldQuantity = bh->getQuantity();
                                    if(boatHoldQuantity >= remainToPay){
                                        activePlayer->removeFromBoatHold(chosenBoatholdId, remainToPay);// à faire plutôt depuis l'engine
                                        remainToPay = 0;
                                        activePlayer->setAmountToPay(remainToPay);
                                    }
                                    else{
                                        activePlayer->removeFromBoatHold(chosenBoatholdId, boatHoldQuantity);
                                        remainToPay = activePlayer->getAmountToPay() - boatHoldQuantity;
                                        activePlayer->setAmountToPay(remainToPay);
                                    }
                                    std::cout << "There remain: " << remainToPay << " " << resTypeToPay << " to pay.\n";
                                }
                            }
                            activePlayer->setHasToPay(false);
                        }
                    }

                    gameInstance->request(); // from resourcehandlingstate to OpponentChoicestate or CardActionState if condition
                    break;


                case OPPONENT_CHOICE_STATE:
                    std::cout << "Client now entering OPPONENT_CHOICE_STATE\r\n" << std::endl;

                    activePlayer->setMustFight(false);
                    hasFought = true;


                    opponentsList = activePlayer->getOpponentsList();
                    for (size_t i = 0; i < opponentsList.size(); ++i) {
                        std::cout << i + 1 << ". " << opponentsList[i]->getName() << "\r\n" << std::endl;
                    }
                    
                    // Pick an opponent
                    if (activePlayer->get_AI()==nullptr){ //real player
                        chosenOpponentId = inputHandler.chooseOpponent(opponentsList.size());
                    }
                    else { // AI input
                        chosenOpponentId = activePlayer->get_AI()->chooseOpponent(opponentsList.size());
                    }
                    
                    //chosenOpponentId = inputHandler.chooseOpponent(opponentsList.size()); //old code
                    chosenOpponentId = opponentsList.at(chosenOpponentId)->getPlayerId();

                    chooseOpponent = new engine::ChooseOpponent(activePlayerIndex, chosenOpponentId);
                    chooseOpponent->launchCommand(gameInstance);
                    delete chooseOpponent;

                    combatPlayer = gameInstance->getDefendingPlayer();
                    std::cout << "You chose this bad guy: " << combatPlayer->getName() << "\r\n" << std::endl;
                    
                    gameInstance->request(); // from OpponentChoiceState to CombatAttackingState
                    break;


                case COMBAT_ATTACKING_STATE:
                    std::cout << "Client now entering COMBAT_ATTACKING_STATE\r\n" << std::endl;
                    
                    //checker que le state se passe après le client : oui

                    //attacking player chooses his canons and rolls combat dice
                    combatPlayer = gameInstance->getAttackingPlayer();
                    playerNbCanons = 0;

                    for (state::BoatHold *bh : combatPlayer->getBoatHolds()){
                        if (bh->hasResourceType("Canon")) {
                            playerNbCanons += bh->getQuantity();
                        }
                    }

                    std::cout << "Atacking Player:" << combatPlayer->getName() << " has: " << playerNbCanons << " Canons.\r\n" << std::endl;
                    if (combatPlayer->get_AI() == nullptr){
                        playerNbCanons = inputHandler.chooseCanonNb(playerNbCanons);
                    }
                    else {
                        playerNbCanons = combatPlayer->get_AI()->chooseCanonNb(playerNbCanons);
                    }
                    chooseCanons = new engine::ChooseCanons(combatPlayer->getPlayerId(), playerNbCanons);
                    chooseCanons->launchCommand(gameInstance);
                    delete chooseCanons;

                    boatHoldCount = combatPlayer->getBoatHolds().size();
                    std::cout << "Player: "<< combatPlayer->getName() << " has to pay: " << playerNbCanons << " Canons.\n";
                    while (playerNbCanons > 0){
                        auto boatHolds = combatPlayer->getBoatHolds();
                        // Pick a boat hold
                        if (combatPlayer->get_AI()==nullptr){ //real player
                            chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                        }
                        else { // AI input
                            chosenBoatholdId = combatPlayer->get_AI()->selectUserBoatHold(boatHoldCount, "Canon", combatPlayer->getPlayerId());
                        }
                        chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                        if(chosenBoatholdResType != "Canon"){
                            std::cout << "Invalid Resource Type. You chose a Boathold with: " << chosenBoatholdResType << ". Please choose a BoatHold with: Canons.\n";
                        }
                        else{
                            state::BoatHold *bh = boatHolds.at(chosenBoatholdId);
                            boatHoldQuantity = bh->getQuantity();
                            if(boatHoldQuantity >= playerNbCanons){
                                combatPlayer->removeFromBoatHold(chosenBoatholdId, playerNbCanons);// à faire plutôt depuis l'engine
                                playerNbCanons = 0;
                            }
                            else{
                                combatPlayer->removeFromBoatHold(chosenBoatholdId, boatHoldQuantity);
                                playerNbCanons = playerNbCanons - boatHoldQuantity;
                            }
                            std::cout << "There remain: " << playerNbCanons << " Canons to pay.\n";
                        }
                    }

                    rollDice = new engine::RollDice(COMBATDIE, combatPlayer->getPlayerId());
                    rollDice->launchCommand(gameInstance);
                    delete rollDice;

                    gameInstance->request(); // from CombatAttackingState to CombatDefendingState or StealResourceState if condition
                    break;


                case COMBAT_DEFENDING_STATE:
                    std::cout << "Client now entering COMBAT_DEFENDING_STATE\r\n" << std::endl;

                    //defending player chooses his canons and rolls combat dice
                    combatPlayer = gameInstance->getDefendingPlayer();
                    playerNbCanons = 0;

                    for (state::BoatHold *bh : combatPlayer->getBoatHolds()){
                        if (bh->hasResourceType("Canon")) {
                            playerNbCanons += bh->getQuantity();
                        }
                    }
                    
                    std::cout << "Defending Player:" << combatPlayer->getName() << " has: " << playerNbCanons << " Canons.\r\n" << std::endl;
                    
                    if (gameInstance->getDefendingPlayer()->get_AI() == nullptr){
                        playerNbCanons = inputHandler.chooseCanonNb(playerNbCanons);
                    }
                    else {
                        playerNbCanons = gameInstance->getDefendingPlayer()->get_AI()->chooseCanonNb(playerNbCanons);
                    }
                    chooseCanons = new engine::ChooseCanons(combatPlayer->getPlayerId(), playerNbCanons);
                    chooseCanons->launchCommand(gameInstance);
                    delete chooseCanons;

                    boatHoldCount = combatPlayer->getBoatHolds().size();
                    std::cout << "Player: "<< combatPlayer->getName() << " has to pay: " << playerNbCanons << " Canons.\n";
                    while (playerNbCanons > 0){
                        auto boatHolds = combatPlayer->getBoatHolds();
                        // Pick a boat hold
                        if (combatPlayer->get_AI()==nullptr){ //real player
                            chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                        }
                        else { // AI input
                            chosenBoatholdId = combatPlayer->get_AI()->selectUserBoatHold(boatHoldCount, "Canon", combatPlayer->getPlayerId());
                        }
                        chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                        if(chosenBoatholdResType != "Canon"){
                            std::cout << "Invalid Resource Type. You chose a Boathold with: " << chosenBoatholdResType << ". Please choose a BoatHold with: Canons.\n";
                        }
                        else{
                            state::BoatHold *bh = boatHolds.at(chosenBoatholdId);
                            boatHoldQuantity = bh->getQuantity();
                            if(boatHoldQuantity >= playerNbCanons){
                                combatPlayer->removeFromBoatHold(chosenBoatholdId, playerNbCanons);// à faire plutôt depuis l'engine
                                playerNbCanons = 0;
                            }
                            else{
                                combatPlayer->removeFromBoatHold(chosenBoatholdId, boatHoldQuantity);
                                playerNbCanons = playerNbCanons - boatHoldQuantity;
                            }
                            std::cout << "There remain: " << playerNbCanons << " Canons to pay.\n";
                        }
                    }
                    rollDice = new engine::RollDice(COMBATDIE, combatPlayer->getPlayerId());
                    rollDice->launchCommand(gameInstance);
                    delete rollDice;

                    gameInstance->request(); // from CombatDefendingState to ResourceHandlingState or StealResourceState if condition
                    break;


                case STEAL_RESOURCE_STATE:
                    std::cout << "Client now entering STEAL_RESOURCE_STATE\r\n" << std::endl;

                    //winner chooses one loser's boatHold to steal and one of his to get stolen Resources
                    winner = gameInstance->getCombatWinner();
                    loser = gameInstance->getCombatLoser();
                    
                    std::cout << "Player: " << winner->getName() << " wins and Player: " << loser->getName() << " loses." << std::endl;

                    std::cout << "Cales de " << loser->getName() << ": " << std::endl;
                    boatHoldCount = 0;
                    isNaked = true;
                    for(state::BoatHold *bh : loser->getBoatHolds()){
                        boatHoldCount++;
                        std::cout<< "BoatHold N°" << boatHoldCount << " : \r\n" << std::endl;
                        isNaked = isNaked && (bh->getResourceType() == "None");
                        bh->showContent();
                    }
                    //should also check the treasures --TODO 
                    if (isNaked){
                        std::cout << loser->getName() << " has no resources left. You couldn't steal anything." << std::endl;
                    }
                    else {
                        validChosenBoathold = false;
                        while(!validChosenBoathold){
                            auto boatHolds = loser->getBoatHolds();
                            // Pick a boat hold
                            if (winner->get_AI()==nullptr){ //real player
                                chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount, true);
                            }
                            else { // AI input
                                chosenBoatholdId = winner->get_AI()->selectUserBoatHold(boatHoldCount);
                            }
                            chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                            boatHoldQuantity = boatHolds.at(chosenBoatholdId)->getQuantity();
                            if(chosenBoatholdResType != "None"){
                                validChosenBoathold = true;
                            }
                            else {
                                std::cout << "You picked an empty hold. You must choose an other hold." << std::endl;
                            }
                        }
                        resTypeToAdd = chosenBoatholdResType;

                        auto boatHolds = winner->getBoatHolds();
                        isFull = true;
                        for (state::BoatHold *bh : boatHolds) {
                            isFull = isFull && bh->hasResourceType(resTypeToAdd);
                        }
                        if(isFull){
                            std::cout << "Player: "<< activePlayer->getName() << " was full and couldn't steal the Resource: " << resTypeToAdd << std::endl;
                        }
                        else {

                            std::cout << "Player: "<< winner->getName() << " receives: " << boatHoldQuantity << " " << resTypeToAdd << ". Please choose a boat hold to store this resource\n";
                            boatHoldCount = winner->getBoatHolds().size();
                            validChosenBoathold = false;
                            while(!validChosenBoathold){
                                // Pick a boat hold
                                if (winner->get_AI()==nullptr){ //real player
                                    winnerBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                                }
                                else { // AI input
                                    winnerBoatholdId = winner->get_AI()->selectUserBoatHold(boatHoldCount);
                                }
                                chosenBoatholdResType = boatHolds.at(winnerBoatholdId)->getResourceType();
                                if(chosenBoatholdResType != resTypeToAdd){
                                    validChosenBoathold = true;
                                }
                                else {
                                    std::cout << "Invalid Boathold Type. You must choose a Boathold without : " << resTypeToAdd << ".\n";
                                }
                            }

                            stealResource = new engine::StealResource(chosenBoatholdId, winner->getPlayerId(), loser->getPlayerId(), winnerBoatholdId);
                            stealResource->launchCommand(gameInstance);
                            delete stealResource;
                        }
                    }
                    activePlayer->setHasToPay(true);
                    gameInstance->request(); // from StealResourceState to ResourceHandlingState
                    break;


                case GAME_OVER_STATE:
                    std::cout << "Client now entering GAME_OVER_STATE\r\n" << std::endl;

                    gameInstance->request(); // display the results
                    endloop = 1; // exit this game mode
                    break;

                default :
                    break;
            }


            //std::cout << "\n\n\nDo you wish to continue the game ? -------------------------------" << std::endl;
            //std::cin >> waitConfirm;
            //if (waitConfirm[0] == 'n'){
            //    endloop = 1;
            //}

        }
        
        std::cout << "\n\nExiting the game loop\n\n\n" << std::endl;
        return 0;
    }

    int Client::runDuelGame()
    {
        return 0;
    }

    int Client::runOnlineGame()
    {
        // Création du socket
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            return 1;
        }

        // Configuration de l'adresse du serveur
        sockaddr_in serverAddr{};
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(53000);
        inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

        // Connexion au serveur
        if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("Connection failed");
            close(sock);
            return 1;
        }

        std::cout << "Connecté au serveur. Tapez 'exit' pour quitter." << std::endl;

        char buffer[1024];
        while (true) {
            // Saisie de l'utilisateur
            std::cout << "Votre commande : ";
            std::string input;
            std::getline(std::cin, input);

            // Envoi de la commande
            if (send(sock, input.c_str(), input.size(), 0) < 0) {
                perror("Erreur lors de l'envoi de la commande");
                break;
            }

            if (input == "exit") {
                std::cout << "Déconnexion." << std::endl;
                break;
            }

            // Réception de la réponse
            memset(buffer, 0, sizeof(buffer));
            int bytesRead = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytesRead > 0) {
                std::cout << "Réponse du serveur : " << buffer << std::endl;
            } else if (bytesRead == 0) {
                std::cout << "Le serveur a fermé la connexion." << std::endl;
                break;
            } else {
                perror("Erreur lors de la réception");
                break;
            }
        }

        close(sock);
        return 0;
    }


    int Client::localGameConfigInit()
    {

        engine::ChooseNbOfPlayers* chooseNbOfPlayers;
        engine::ChooseAI* chooseAI;
        engine::ChoosePlayerName* choosePlayerName;
        engine::ChooseMapSize* chooseMapSize;
        engine::ResourceManager* resourceManager;
        
        state::Game *gameInstance = gameEngine->game;
        gameInstance->setTurn(0);

        // Sets number of player
        int playerNumber = inputHandler.getNumberofPlayers();
        std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;
        nbPlayerChosen=true;
        chooseNbOfPlayers = new engine::ChooseNbOfPlayers(playerNumber);
        chooseNbOfPlayers->launchCommand(gameInstance);
        delete chooseNbOfPlayers;

        // Sets players' name and choose AIs ?
        state::Player* currentPlayer;
        int levelAI = 0;
        for(int playerIndex = 0; playerIndex < playerNumber; playerIndex++){
            isPlayerTypeChosen=false;
            gameInstance->setActivePlayer(gameInstance->getPlayerList().at(playerIndex));

            // Set the AI
            std::string playerName;
            levelAI = inputHandler.pickAnAI(playerIndex);
            currentPlayer = gameInstance->getActivePlayer();
            chooseAI = new engine::ChooseAI(levelAI, playerIndex);
            chooseAI->launchCommand(gameInstance);
            // Set the username
            if (currentPlayer->get_AI()==nullptr){ //real player
                playerName = inputHandler.getPlayerName(playerIndex);
            }
            else { // AI input
                playerName = currentPlayer->get_AI()->getPlayerName(playerIndex);
            }
            choosePlayerName = new engine::ChoosePlayerName(playerIndex, playerName);
            choosePlayerName->launchCommand(gameInstance);
            delete choosePlayerName;
        }
        allPlayerSet=true;
        // Sets MapSize
        int mapSize = inputHandler.getMapSize();
        std::cout <<"MapSize set to: " << std::to_string(mapSize)<< std::endl;
        chooseMapSize = new engine::ChooseMapSize(mapSize);
        chooseMapSize->launchCommand(gameInstance);
        delete chooseMapSize;

        // Init players' position, treasures, gold, food
        const std::vector<state::Player*>& playingPlayers = gameInstance->getPlayerList();
        for (state::Player* player : playingPlayers) {
            player->setPosition(0);
            std::vector<state::Treasure> initialTreasures = { state::Treasure(0, 0) };
            player->setTreasures(initialTreasures);
            auto goldResource = make_unique<state::Gold>();
            resourceManager->addResourcesToBoathold(player,std::move(goldResource), 3, 0);
            auto foodResource = make_unique<state::Food>();
            resourceManager->addResourcesToBoathold(player,std::move(foodResource), 3, 1);    
        }

        // Displays Tiles' cost
        // Utiliser les blocs suivants pour gérer facilement le render !
        printf("Affichage de la map :\n");
        std::cout<<"Tuile N°0 : Cette case représente Port Royal, il n'y a rien à payer ici." << std::endl;
        for (int i = 1; i < mapSize; i++) {
            std::cout<< "Tuile N°" << i << " contient : ";
            if(gameInstance->map->getResourceCost(i)>0) {
                std::cout<<"Il y a "<<gameInstance->map->getResourceCost(i)<< " " <<gameInstance->map->getResourceType(i)<< " à payer sur cette tuile." << std::endl;
            }
            if(gameInstance->map->getResourceType(i)=="Treasure") {
                std::cout<<"Il y a un "<<gameInstance->map->getResourceType(i)<< " à gagner sur cette tuile." << std::endl;
            }
        }

        // Displays players' boatholds
        for(state::Player * player : gameInstance->getPlayerList()) {
            int i=0;
            std::cout<< "Cales de "<< player->getName()<<" :" << std::endl;
            for (state::BoatHold *bh:player->getBoatHolds()) {
                std::cout<< "BoatHold N°" << i << " : " ;
                bh->showContent();
                i++;
            }
            std::cout<< "Trésors de "<< player->getName()<<" :" << std::endl;
        }

        //Un std::unique_ptr est un pointeur intelligent qui garantit
        //qu'il ne peut y avoir qu'un seul propriétaire de l'objet
        //pointé, assurant ainsi une gestion mémoire automatique et
        //une prévention des fuites de mémoire.
        //En utilisant std::move, cela transfère directement l’objet
        //au lieu d'en faire une copie, ce qui est essentiel pour les
        //unique_ptr car ils ne peuvent pas être copiés. Sans std::move,
        //cela ne compilerait pas car un unique_ptr ne supporte pas la copie

        return 0;
    }
    void Client::update(const std::string &eventType, const std::string &data){
        //la je lance une commande je sais pas trop comment
        if (eventType == "chooseNbOfPlayers"){
            engine::ChooseNbOfPlayers* chooseNbOfPlayers = new engine::ChooseNbOfPlayers(stoi(data));
            chooseNbOfPlayers->launchCommand(gameInstance);
            gameInstance->getPlayerList();
            std::cout << gameInstance->getPlayerList().size() << std::endl;
        }
    }
    
    Client::~Client()
    {
    }
}
