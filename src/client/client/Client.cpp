#include "client.h"
#include "state.h"
#include "state/Player.h"
#include "../shared/engine/ResourceManager.h"
#include "../shared/engine/ChooseNbOfPlayers.h"
#include "../shared/engine/ChoosePlayerName.h"
#include "../shared/engine/ChooseMapSize.h"
#include "../shared/engine/AddToBoathold.h"
#include "../shared/engine/AssignDice.h"
#include "../shared/engine/ChooseCanons.h"
#include "../shared/engine/ChooseCard.h"
#include "../shared/engine/ChooseOpponent.h"
#include "../shared/engine/ChoosePath.h"
#include "../shared/engine/RollDice.h"
#include "../shared/engine/StealResource.h"
//#include "../shared/engine.h"

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
#define GOLD 1
#define FOOD 2

#define EXIT_GAME 0
#define LOCAL_MULTIPLAYER 1
#define ONLINE_MULTIPLAYER 2
#define SINGLE_PLAYER 3
#define LOCAL_AND_AI 4


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
        gameEngine = new engine::GameEngine(gameState);
        gameInstance = gameEngine->game;
        InputHandler inputHandler;
    }

    int Client::launch(){
        // Playing Modes
        running=true;
        //renderer-> show the correct window
        int playingMode = 1;
        while(playingMode){
            playingMode = inputHandler.selectGameMode();
            switch (playingMode){
                case EXIT_GAME :
                    break;
                case LOCAL_MULTIPLAYER :
                    runLocalGame();
                    break;
                case ONLINE_MULTIPLAYER :
                    runOnlineGame();
                    break;
                case SINGLE_PLAYER :
                    runSoloGame();
                    break;

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

        //!!!!! IMPORTANT !!!!!
        // notre client vole le rôle de l'engine
        // il faut faire GameEngine->fcn() à chaque fois que l'on modifie la valeur d'une variable de game avec un "set" ou un "="

        int gameState = gameInstance->state->getStateId();

        // Init every game loop variable
        int numberOfPlayers = gameInstance->getPlayerList().size();
        int actionCounter;
        int activePlayerIndex;
        int captainIndex;
        int die1;
        int die2;
        bool chosenDice;
        state::Player* activePlayer;
        int chosenCardId;

        // Init every game loop command
        engine::AssignDice* assignDice;
        engine::ChooseCard* chooseCard;
        engine::AddToBoathold* addToBoathold; //unused
        engine::ResourceManager* resourceManager; //unused
        engine::ChoosePath* choosePath; //unused
        engine::ChooseCanons* chooseCanons; //unused
        engine::ChoosePlayerName* choosePlayerName; //unused

        // Game loop State behavior
        int endloop = 0;
        std::string waitConfirm;
        std::cout << "Client now entering the game loop\r\n" << std::endl;
        while (!endloop){

            gameState = gameInstance->state->getStateId();

            switch (gameState){

                case GAME_CONFIG_STATE:
                    std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
                    gameConfigInit(); // is the gameconfiginit the same for every playing mode ?
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
                    gameInstance->actionCounter = 0;
                    die1 = rand()%6+1;
                    die2 = rand()%6+1;
                    captainIndex = gameInstance->getCaptainIndex();
                    std::cout << "Capitaine " << captainIndex << " choisissez vos dés ! \r\n" << std::endl;
                    chosenDice = inputHandler.chooseTimeDice(die1, die2);
                    if (chosenDice == 1){assignDice = new engine::AssignDice(die1, die2);}
                    else{assignDice = new engine::AssignDice(die2, die1);}
                    assignDice->launchCommand(gameInstance);
                    gameInstance->request();
                    break;


                case CARD_CHOICE_STATE:

                    std::cout << "Client now entering CARD_CHOICE_STATE\r\n" << std::endl;
                    captainIndex = gameInstance->getCaptainIndex();

                    // partie réseau

                    // l'InputHandler affiche un message personnalisé "joueur truc choisis tes cartes"
                    // la boucle for en dessous n'existera pas tout le monde choisi en même temps
                    // pas d'active player pour le choosecard

                    // Every Player choose 1 Card in their own cardDeck
                    for(int i = 0; i < numberOfPlayers; i++) {
                        activePlayerIndex = (captainIndex + i) % numberOfPlayers;
                        gameInstance->setActivePlayerIndex(activePlayerIndex);
                        gameInstance->setActivePlayer(gameInstance->getPlayerList().at(activePlayerIndex));
                        activePlayer = gameInstance->getActivePlayer();
                        std::cout << "Player " << activePlayer->getPlayerId() << "'s turn. Choose your card wisely." << std::endl;
                        gameInstance->displayState();
                        chosenCardId = inputHandler.chooseCardFromHand(activePlayer->getHandCards());
                        chooseCard = new engine::ChooseCard(activePlayer, chosenCardId);
                        chooseCard->launchCommand(gameInstance);
                    }

                    gameInstance->request();
                    break;


                case CARD_ACTION_STATE:
                    std::cout << "Client now entering CARD_ACTION_STATE\r\n" << std::endl;
                    actionCounter = gameInstance->actionCounter;

                    // partie réseau

                    // on garde boucle for avec activePlayer

                    for(int i = 0; i < numberOfPlayers; i++) {
                        std::cout << "Action number " << actionCounter << "\r\n" << std::endl;
                        activePlayerIndex = (captainIndex + i) % numberOfPlayers;
                        gameInstance->setActivePlayerIndex(activePlayerIndex);
                        gameInstance->setActivePlayer(gameInstance->getPlayerList().at(activePlayerIndex));
                        activePlayer = gameInstance->getActivePlayer();
                        std::cout << "Player " << activePlayer->getPlayerId() << " do you Action. Dew it." << std::endl;
                        gameInstance->displayState();
                        //chosenCardId = inputHandler.chooseCardFromHand(activePlayer->getHandCards());
                        //chooseCard = new engine::ChooseCard(activePlayer, chosenCardId);
                        //chooseCard->launchCommand(gameInstance);

                    }

                    gameInstance->setActivePlayerIndex((captainIndex + 1) % numberOfPlayers);

                    /*                    
                    //fin des actions de tous les joueurs
                    if(actionCounter > game->getPlayerList().size()*3) {
                        
                        //update of Captain player
                        
                        gameTurn++; 
                        game->setTurn(gameTurn);
                        game->setActivePlayerIndex(0);
                        int captainIndex = game->getCaptainIndex();
                        captainIndex = (captainIndex + 1) % playerNb;
                        game->setCaptainIndex(captainIndex);
                        game->setActivePlayer(game->getPlayerList().at(captainIndex));
                        std::cout << "Starting a new round in the Playerlist." << std::endl;
                    }
                    */

                    gameInstance->request();
                    break;


                case RESOURCE_HANDLING_STATE:
                    std::cout << "Client now entering RESOURCE_HANDLING_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();
                break;


                case OPPONENT_CHOICE_STATE:
                    std::cout << "Client now entering OPPONENT_CHOICE_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();
                    break;


                case COMBAT_ATTACKING_STATE:
                    std::cout << "Client now entering COMBAT_ATTACKING_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();
                    break;


                case COMBAT_DEFENDING_STATE:
                    std::cout << "Client now entering COMBAT_DEFENDING_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();
                    break;


                case STEAL_RESOURCE_STATE:
                    std::cout << "Client now entering STEAL_RESOURCE_STATE\r\n" << std::endl;
                    //do command truc
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

    int Client::runSoloGame()
    {
        return 0;
    }

    int Client::runOnlineGame()
    {
        return 0;
    }


    int Client::gameConfigInit()
    {

        state::Game *gameInstance = gameEngine->game;

        // Sets number of player
        int playerNumber = inputHandler.getNumberofPlayers();
        std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;
        engine::ChooseNbOfPlayers* chooseNbOfPlayers = new engine::ChooseNbOfPlayers(playerNumber);
        chooseNbOfPlayers->launchCommand(gameInstance);
        delete chooseNbOfPlayers;

        // Sets players' name
        for(int playerIndex = 0; playerIndex < playerNumber; playerIndex++){
            std::string playerName = inputHandler.getPlayerName(playerIndex);
            engine::ChoosePlayerName* choosePlayerName = new engine::ChoosePlayerName(playerIndex, playerName);
            choosePlayerName->launchCommand(gameInstance);
            delete choosePlayerName;
        }

        // Sets MapSize
        int mapSize = inputHandler.getMapSize();
        std::cout <<"MapSize set to: " << std::to_string(mapSize)<< std::endl;
        engine::ChooseMapSize* chooseMapSize = new engine::ChooseMapSize(mapSize);
        chooseMapSize->launchCommand(gameInstance);
        delete chooseMapSize;

        // Init players' position, treasures, gold, food
        const std::vector<state::Player*>& playingPlayers = gameInstance->getPlayerList();
        for (state::Player* player : playingPlayers) {
            player->setPosition(0);
            std::vector<state::Treasure> initialTreasures = { state::Treasure(0, 0) };
            player->setTreasures(initialTreasures);
            auto goldResource = make_unique<state::Gold>();
            engine::ResourceManager resource_manager;
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

        // to be continued

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
}

