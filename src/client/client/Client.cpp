#include "client.h"
#include "state.h"
#include "state/Player.h"
#include "../shared/engine.h"

#include <iostream>
#include <limits>
#include <bits/unique_ptr.h>
#include "Client.h"

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
    Client::Client()
    {
        // Instantiates a new Game context and runs concrete state GameConfigState
        Renderer renderer; //unused
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
            //wait user confirmation
            std::cin >> waitConfirm;
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
        int die1;
        int die2;
        bool chosenDice;
        state::Player* activePlayer;
        int chosenCardId;
        state::ActionCard *actionCard;
        int chosenBoatholdId;
        std::string chosenBoatholdResType;
        int boatHoldCount;
        int remainToPay;
        std::string resTypeToPay;
        int boatHoldQuantity;
        std::string resTypeToAdd;
        int actionType;
        int currentDie;
        bool validChosenBoathold;
        int chosenOpponentId;
        std::vector<state::Player *> opponentsList;
        state::Player* combatPlayer;
        int playerNbCanons;
        state::Player* winner;
        state::Player* loser;

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
                
                    localGameConfigInit(); // is the soloGameConfigInit the same for every playing mode ?

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
                            chosenOpponentId = inputHandler.chooseCardFromHand(activePlayer->getHandCards());
                        }
                        else { // AI input
                            chosenOpponentId = activePlayer->get_AI()->chooseCardFromHand(activePlayer->getHandCards());
                        }
                        //chosenCardId = inputHandler.chooseCardFromHand(activePlayer->getHandCards()); //old code
                        chooseCard = new engine::ChooseCard(activePlayer, chosenCardId);
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
                    gameInstance->setActivePlayer(gameInstance->getPlayerList().at(activePlayerIndex));
                    activePlayer = gameInstance->getActivePlayer();
                    std::cout << "player: " << activePlayer->getName() << " activePlayerIndex: "<< activePlayerIndex << " id: " << activePlayer->getPlayerId() << " Do your Action. Dew it.\r\n" << std::endl;                                

                    activePlayer->setPrevDuel(false);
                    activePlayer->setHasMoved(false);

                    // logique de déplacement sans input
                    chosenCardId = activePlayer->getActiveCard();
                    // checks if current action is a movement or a Resource, do we use resourceManager ?
                    actionCard = state::Game::collectionOfCards.at(chosenCardId);
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
                        activePlayer->setHasMoved(true);
                        activePlayer->moveWithDirection(currentDie, 1);
                        break;
                    case MOVE_BACKWARD:
                        activePlayer->setHasMoved(true);
                        activePlayer->moveWithDirection(currentDie, -1);
                        break;
                    case ADD_FOOD:
                        resTypeToAdd = "Food";
                        break;
                    case ADD_GOLD:
                        resTypeToAdd = "Gold";
                        break;
                    case ADD_CANONS:
                        resTypeToAdd = "Canon";
                        break;
                    default:
                        break;
                    }
                    if(actionType != MOVE_BACKWARD && actionType != MOVE_FORWARD){
                        std::cout << "Player: "<< activePlayer->getName() << " receives: " << currentDie << " " << resTypeToAdd << ", Please choose a BoatHold to store this Resource\n";
                        validChosenBoathold = false;
                        while(!validChosenBoathold){
                            auto boatHolds = activePlayer->getBoatHolds();
                            // Pick a boat hold
                            if (activePlayer->get_AI()==nullptr){ //real player
                                chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount);
                            }
                            else { // AI input
                                chosenBoatholdId = activePlayer->get_AI()->selectUserBoatHold(boatHoldCount);
                            }
                            //chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount); //old code
                            chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                            if(chosenBoatholdResType == resTypeToAdd){
                                std::cout << "Invalid Boathold Type. You must choose a Boathold without : " << resTypeToAdd << ".\n";
                                continue;
                            }
                            validChosenBoathold = true;
                        }
                        addToBoathold = new engine::AddToBoathold(activePlayerIndex, chosenBoatholdId + 1, currentDie, resTypeToAdd);
                        addToBoathold->launchCommand(gameInstance);
                        delete addToBoathold;
                    }

                    std::cout << "player: " << activePlayer->getName() << " activePlayerIndex: " << activePlayerIndex << " id: " << activePlayer->getPlayerId() << " position: "<< activePlayer->getPosition() << "\r\n"<< std::endl;
                    
                    actionCounter += 1;
                    gameInstance->actionCounter = actionCounter;
                    
                    gameInstance->request(); // from cardactionstate to resourcehandlingstate or captaindicestate if condition
                    break;


                case RESOURCE_HANDLING_STATE:
                    std::cout << "Client now entering RESOURCE_HANDLING_STATE\r\n" << std::endl;

                    //player selects boatholds to pay
                    //prevents from paying two times the same tile
                    if(activePlayer->getHasToPay() && activePlayer->getHasMoved()){
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
                                chosenBoatholdId = activePlayer->get_AI()->selectUserBoatHold(boatHoldCount);
                            }
                            //chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount); //old code
                            chosenBoatholdResType = boatHolds.at(chosenBoatholdId)->getResourceType();
                            if(chosenBoatholdResType != resTypeToPay){
                                std::cout << "Invalid Resource Type. You chose a Boathold with: " << chosenBoatholdResType << " Please choose a BoatHold with: " << resTypeToPay << ".\n";
                                continue;
                            }
                            state::BoatHold *bh = boatHolds.at(chosenBoatholdId);
                            boatHoldQuantity = bh->getQuantity();
                            if(boatHoldQuantity >= remainToPay){
                                activePlayer->removeFromBoatHold(chosenBoatholdId, remainToPay);// à faire dans une nouvelle commande
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
                        activePlayer->setHasToPay(false);
                    }

                    gameInstance->request(); // from resourcehandlingstate to OpponentChoicestate or CardActionState if condition
                    break;


                case OPPONENT_CHOICE_STATE:
                    std::cout << "Client now entering OPPONENT_CHOICE_STATE\r\n" << std::endl;
                        
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
                    
                    //checker que le state se passe après le client

                    //attacking player chooses his canons and rolls combat dice
                    combatPlayer = gameInstance->getAttackingPlayer();
                    playerNbCanons = 0;

                    for (state::BoatHold *bh : combatPlayer->getBoatHolds()){
                        if (bh->hasResourceType("Canon")) {
                            playerNbCanons += bh->getQuantity();
                        }
                    }

                    std::cout << "Atacking Player:" << combatPlayer->getName() << " has: " << playerNbCanons << " Canons.\r\n" << std::endl;

                    playerNbCanons = inputHandler.chooseCanonNb(playerNbCanons);
                    chooseCanons = new engine::ChooseCanons(combatPlayer->getPlayerId(), playerNbCanons);
                    chooseCanons->launchCommand(gameInstance);
                    delete chooseCanons;

                    rollDice = new engine::RollDice(COMBATDIE, combatPlayer->getPlayerId());
                    rollDice->launchCommand(gameInstance);
                    delete rollDice;

                    gameInstance->request(); // from CombatAttackingState to CombatDefendingState or StealResourceState if condition
                    break;


                case COMBAT_DEFENDING_STATE:
                    std::cout << "Client now entering COMBAT_DEFENDING_STATE\r\n" << std::endl;

                    //checker que le state se passe après le client

                    //defending player chooses his canons and rolls combat dice
                    combatPlayer = gameInstance->getDefendingPlayer();
                    playerNbCanons = 0;

                    for (state::BoatHold *bh : combatPlayer->getBoatHolds()){
                        if (bh->hasResourceType("Canon")) {
                            playerNbCanons += bh->getQuantity();
                        }
                    }
                    
                    std::cout << "Defending Player:" << combatPlayer->getName() << " has: " << playerNbCanons << " Canons.\r\n" << std::endl;

                    playerNbCanons = inputHandler.chooseCanonNb(playerNbCanons);
                    chooseCanons = new engine::ChooseCanons(combatPlayer->getPlayerId(), playerNbCanons);
                    chooseCanons->launchCommand(gameInstance);
                    delete chooseCanons;

                    rollDice = new engine::RollDice(COMBATDIE, combatPlayer->getPlayerId());
                    rollDice->launchCommand(gameInstance);
                    delete rollDice;

                    gameInstance->request(); // from CombatDefendingState to CardActionState or StealResourceState if condition
                    break;


                case STEAL_RESOURCE_STATE:
                    std::cout << "Client now entering STEAL_RESOURCE_STATE\r\n" << std::endl;

                    //winner chooses a boatHold to steal from loser
                    winner = gameInstance->getCombatWinner();
                    loser = gameInstance->getCombatLoser();

                    std::cout << "Cales de " << loser->getName() << ": " << std::endl;
                    boatHoldCount = 0;
                    for(state::BoatHold *bh : loser->getBoatHolds()){
                        std::cout<< "BoatHold N°" << boatHoldCount << " : \r\n" << std::endl;
                        bh->showContent();
                        boatHoldCount++;
                    }

                    boatHoldCount = loser->getBoatHolds().size();
                    chosenBoatholdId = inputHandler.selectUserBoatHold(boatHoldCount, true);
                    stealResource = new engine::StealResource(chosenBoatholdId, winner->getPlayerId(), loser->getPlayerId());
                    stealResource->launchCommand(gameInstance);
                    delete stealResource;

                    gameInstance->request();
                    break;


                case GAME_OVER_STATE:
                    std::cout << "Client now entering GAME_OVER_STATE\r\n" << std::endl;
                    //do command truc
                    
                    gameInstance->request();
                    endloop = 1;
                    break;

                default :
                    break;
            }


            std::cout << "Do you wish to continue the game ?" << std::endl;
            std::cin >> waitConfirm;
            if (waitConfirm[0] == 'n'){
                endloop = 1;
            }

        }
        return 0;
    }

    int Client::runDuelGame()
    {
        return 0;
    }

    int Client::runOnlineGame()
    {
        return 0;
    }


    int Client::localGameConfigInit()
    {

        engine::ChooseNbOfPlayers* chooseNbOfPlayers;
        engine::ChooseAI* chooseAI;
        engine::ChoosePlayerName* choosePlayerName;
        engine::ChooseMapSize* chooseMapSize;
        engine::ResourceManager resource_manager;
        
        state::Game *gameInstance = gameEngine->game;
        gameInstance->setTurn(0);
        // Sets number of player
        int playerNumber = inputHandler.getNumberofPlayers();
        std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;
        chooseNbOfPlayers = new engine::ChooseNbOfPlayers(playerNumber);
        chooseNbOfPlayers->launchCommand(gameInstance);
        delete chooseNbOfPlayers;

        // Sets players' name and choose AIs ?
        state::Player* currentPlayer;
        int levelAI = 0;
        for(int playerIndex = 0; playerIndex < playerNumber; playerIndex++){

            // Set the AI
            std::string playerName;
            levelAI = inputHandler.pickAnAI(playerIndex);
            currentPlayer = gameInstance->getPlayerList().at(playerIndex);
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
            resource_manager.addResourcesToBoathold(player,std::move(goldResource), 3,1);
            auto foodResource = make_unique<state::Food>();
            resource_manager.addResourcesToBoathold(player,std::move(foodResource), 3,2);    
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
    void Client::update()
    {
    }
    
    Client::~Client()
    {
    }
}
