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



template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


namespace client {
    Client::Client()
    {

        //-----------------------------
        // instantiates a new Game context and runs concrete states "GameConfig" then "Playing" functions
        //-----------------------------
        Renderer renderer;
        gameState = new state::GameConfigState();
        gameEngine = new engine::GameEngine(gameState);
        InputHandler inputHandler;

    }

    int Client::launch(){

        //renderer-> show the correct window
        int exiting = 0;
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
            std::cin >> waitConfirm; //wait user confirmation
        }
        return 0;


    }

    int Client::runLocalGame(){

        state::Game *gameInstance = gameEngine->game;
        gameState = new state::GameConfigState();
        // Old method :
        // gameEngine->steps();


        // New method :


        // case where gameState is GAME_CONFIG_STATE:
        std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
        //do command truc
        gameConfigInit();

        int endloop = 0;
        std::string waitConfirm;
        std::cout << "Client now entering the game loop\r\n" << std::endl;
        int die1;
        int die2;
        bool chosenDice;
        engine::AssignDice* dice;
        int state;
        while (!endloop){
            //state=gameState->getStateId();
            state=gameInstance->state->getStateId();
            //on s'arrête là
            switch (state){//gameState->getStateId()/*test1*/){
                case GAME_CONFIG_STATE:
                    std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();

                    break;


                case CAPTAIN_DICE_STATE:
                    std::cout << "Client now entering CAPTAIN_DICE_STATE\r\n" << std::endl;
                    die1=rand()%6+1;
                    die2=rand()%6+1;
                    chosenDice=inputHandler.chooseTimeDice(die1,die2);
                    if (chosenDice==1){dice= new engine::AssignDice(die1,die2);}
                    else{dice= new engine::AssignDice(die2,die1);}
                    dice->launchCommand(gameInstance);
                    gameInstance->request();
                    break;


                case CARD_CHOICE_STATE:
                    std::cout << "Client now entering CARD_CHOICE_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();
                    break;


                case CARD_ACTION_STATE:
                    std::cout << "Client now entering CARD_ACTION_STATE\r\n" << std::endl;
                    //do command truc
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


                case GAME_OVER_STATE:
                    std::cout << "Client now entering GAME_OVER_STATE\r\n" << std::endl;
                    //do command truc
                    gameInstance->request();
                    endloop = 1;
                    break;

                default :
                    break;
            }



            std::cout << "Souhaitez vous continuer le jeu ?" << std::endl;
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

        int playerNumber = inputHandler.getNumberofPlayers();
        std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;
        engine::ChooseNbOfPlayers* chooseNbOfPlayers = new engine::ChooseNbOfPlayers(playerNumber);
        chooseNbOfPlayers->launchCommand(gameInstance);
        delete chooseNbOfPlayers;

        for(int playerIndex = 0; playerIndex < playerNumber; playerIndex++){
            std::string playerName = inputHandler.getPlayerName(playerIndex);
            engine::ChoosePlayerName* choosePlayerName = new engine::ChoosePlayerName(playerIndex, playerName);
            choosePlayerName->launchCommand(gameInstance);
            delete choosePlayerName;
        }

        int mapSize = inputHandler.getMapSize();
        std::cout <<"MapSize set to: " << std::to_string(mapSize)<< std::endl;
        engine::ChooseMapSize* chooseMapSize = new engine::ChooseMapSize(mapSize);
        chooseMapSize->launchCommand(gameInstance);
        delete chooseMapSize;

        //-------------Initializes players' parameters------------

        const std::vector<state::Player*>& playingPlayers = gameInstance->getPlayerList();
        for (state::Player* player : playingPlayers) {
            player->setPosition(0);
            // Treasure(bonus, malus)
            std::vector<state::Treasure> initialTreasures = { state::Treasure(0, 0) };
            player->setTreasures(initialTreasures);
            auto goldResource = make_unique<state::Gold>();
            engine::ResourceManager resource_manager;//A vire
            resource_manager.addResourcesToBoathold(player,std::move(goldResource), 3,1);
            auto foodResource = make_unique<state::Food>();
            resource_manager.addResourcesToBoathold(player,std::move(foodResource), 3,2);
            //delete &resource_manager;   //bad idea         
        }

        // Utiliser les blocs suivants pour gérer facilement le render !
        printf("Affichage de la map :\n");
        std::cout<<"Tuile N°0 : Cette case représente Port Royal, il y a rien à payer ici." << std::endl;
        for (int i = 1; i < mapSize; i++) {
            std::cout<< "Tuile N°" << i << " contient : ";
            if(gameInstance->map->getResourceCost(i)>0) {
                std::cout<<"Il y a "<<gameInstance->map->getResourceCost(i)<< " " <<gameInstance->map->getResourceType(i)<< " à payer sur cette tuile." << std::endl;
            }
            if(gameInstance->map->getResourceType(i)=="Treasure") {
                std::cout<<"Il y a un "<<gameInstance->map->getResourceType(i)<< " à gagner sur cette tuile." << std::endl;
            }
        }

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




        // //-------------Initializes players' parameters------------
        // const std::vector<state::Player*>& playingPlayers = game->getPlayerList();
        // for (state::Player* player : playingPlayers) {
        //   player->setPosition(0);
        //   // Treasure(bonus, malus)
        //   std::vector<state::Treasure> initialTreasures = { state::Treasure(0, 0) };
        //   player->setTreasures(initialTreasures);

        // BoatHold()
        //définir setBoatHolds
        // Gold() + Food()
        //Un std::unique_ptr est un pointeur intelligent qui garantit
        //qu'il ne peut y avoir qu'un seul propriétaire de l'objet
        //pointé, assurant ainsi une gestion mémoire automatique et
        //une prévention des fuites de mémoire.
        //En utilisant std::move, cela transfère directement l’objet
        //au lieu d'en faire une copie, ce qui est essentiel pour les
        //unique_ptr car ils ne peuvent pas être copiés. Sans std::move,
        //cela ne compilerait pas car un unique_ptr ne supporte pas la copie


        //       auto goldResource = make_unique<state::Gold>();
        //       engine::ResourceManager resource_manager;//A vire
        //       resource_manager.addResourcesToBoathold(player,std::move(goldResource), 3,1);
        //       auto foodResource = make_unique<state::Food>();
        //       resource_manager.addResourcesToBoathold(player,std::move(foodResource), 3,2);
        //       int i=1;
        //       for (state::BoatHold *bh: player->getBoatHolds()) {
        //         std::cout<< "BoatHold N°" << i << " : " ;
        //         bh->showContent();
        //         i++;
        //       }

        //       // print le type et nombre de ressource du boathold : void BoatHold::showContents()
        //       game->displayState();

        //       std::cout<<"Player " << std::to_string(player->getPlayerId()) <<" (" + player->getName() << ") initialized at position " << std::to_string(player->getPosition())<< std::endl;
        //     }
        //     std::cout<<"Players initialized: " << std::to_string(playingPlayers.size()) << " players in the game."<< std::endl;

        return 0;
    }
}

