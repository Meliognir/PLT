#include "client.h"
#include "state.h"
#include "state/Player.h"
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


namespace client{

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
    std::string modeInput;
    while(!exiting){
        //cliquer aux bons endroits pour choisir le mode de jeu souhaité
        std::cout << "Select a Game Mode" << std::endl;
        std::cin >> modeInput;

        //switch (playingMode)
        //{
        //case /* constant-expression */:
            /* code */
            /*break;
        
        default:
            break;
        }*/

        //case local :
        /*
        runLocalGame()
        exiting = 1;  */     
    }


}

int Client::runLocalGame(){

    state::Game *gameInstance = gameEngine->game;

    // Old method :
    // gameEngine->steps();


    // New method : 


    // case where gameState is GAME_CONFIG_STATE:
    std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
        //do command truc
        gameConfigInit();
        gameInstance->request();

    int endloop = 0;
    std::string waitConfirm;
    std::cout << "Client now entering the game loop\r\n" << std::endl;

    while (!endloop){

        switch (gameState->getStateId()/*test1*/){


            case GAME_CONFIG_STATE:
                std::cout << "Client now entering GAME_CONFIG_STATE\r\n" << std::endl;
                //do command truc
                gameInstance->request();
            break;


            case CAPTAIN_DICE_STATE:
                std::cout << "Client now entering CAPTAIN_DICE_STATE\r\n" << std::endl;
                //do command truc
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

        }

        std::cout << "Souhaitez vous continuer le jeu ?" << std::endl;
        std::cin >> waitConfirm;
        if (waitConfirm[0] == 'n'){
            endloop = 1;
        }

    }
    return 0;
}


int Client::gameConfigInit(){

    state::Game *gameInstance = gameEngine->game;

    int playerNumber = inputHandler.getNumberofPlayers();
    std::cout <<"Number of players set to: " << std::to_string(playerNumber)<< std::endl;
    engine::ChooseNbOfPlayers* chooseNbOfPlayers = new engine::ChooseNbOfPlayers(playerNumber);
    chooseNbOfPlayers->launchCommand(gameInstance);
    delete chooseNbOfPlayers;

    for(int playerIndex; playerIndex < playerNumber; playerIndex++){
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

//ChoosePlayerName.launchcommand(gameInstance)

//ChooseMapSize.launchcommand(gameInstance)

    // std::vector<state::Player*> players={};

    // int mapSize = inputHandler.getMapSize();//A vire
    // //-------------Initializes Map + tiles------------
    
    // while(mapSize <= 1){
    //   std::cout << "Enter the size of the map: ";
    //   std::cin >> mapSize;
    //   if (std::cin.fail()) { 
    //       std::cin.clear();   
    //       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    //       std::cout << "Invalid input. Please enter a number." << std::endl;
    //       mapSize = 0; 
    //   } else if(mapSize <= 1){
    //     std::cout << "Invalid map size. Please enter a number higher than 1." << std::endl;
    //   }
    // }
    // if (game->map == nullptr) {
    //     game->map = new state::Map(mapSize);
    // } else {
    //     game->map->setSize(mapSize);
    //     game->map->listOfTiles.clear();
    // }

    // int playerNumber = game->getPlayerList().size();
    // //"Port Royal" : Start Tile : foodCost, goldCost, treasure, nbPlayer
    // state::Tile tile(0, "Port Royal", playerNumber);
    // game->map->listOfTiles.push_back(&tile);
    // // other Tiles
    // for (int i = 0; i < mapSize-1; ++i) {
    //   int resource = TREASURE;
    //   int cost = rand()%4;
    //   if (cost){
    //     resource = 1+rand()%2;
    //   }

    //   state::Tile *tile;
    //   if (resource == TREASURE){
    //     tile = new state::Tile(cost, "Treasure", 0);
    //   }
    //   if (resource == FOOD){
    //     tile = new state::Tile(cost, "Food", 0);
    //   }
    //   if (resource == GOLD){
    //     tile = new state::Tile(cost, "Gold", 0);
    //   }
    //   game->map->listOfTiles.push_back(tile);
    // }

    // //std::cout << "Map initialized with " << game->map->getSize() << " tiles." << std::endl;
    // std::cout<<"Map initialized with " << std::to_string(game->map->getSize()) << " tiles."<< std::endl;
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
    }

}