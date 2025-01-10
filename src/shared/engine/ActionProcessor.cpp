// #include "ActionProcessor.h"
// #include "../state.h"
// #include <iostream>

// /* -------------------------------------------- */
// /* -----------Aurélien works here ------------- */
// /* -------------------------------------------- */

// #define DAY true
// #define NIGHT false

// #define FORWARD 1
// #define BACKWARD -1

// #define MOVE_FORWARD 0
// #define MOVE_BACKWARD 1
// #define ADD_FOOD 2
// #define ADD_GOLD 3
// #define ADD_CANONS 4

// template <typename T, typename... Args>
// std::unique_ptr<T> make_unique(Args&&... args) {
//     return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
// }


// namespace engine {
// void ActionProcessor::performAction(state::Player *player, int cardId) {
//     state::ActionCard *actionCard = state::Game::collectionOfCards.at(cardId);
//     static ResourceManager resourceManager;
//     MapManager mapManager;
//     int actionType;
//     int actionValue;
//     auto foodResource = make_unique<state::Food>();
//     auto goldResource = make_unique<state::Gold>();
//     auto canonResource = make_unique<state::Canon>();
//     // lire l'action selon si c'est le jour ou le matin
//     if (state::Game::time == DAY){
//         actionType = actionCard->getDayAction();
//         actionValue = state::Game::dayDie;
//     }

//     if (state::Game::time == NIGHT){
//         actionType = actionCard->getNightAction();
//         actionValue = state::Game::nightDie;
//     }

//     switch (actionType)
//     {
//         case MOVE_FORWARD:
//             mapManager.movePlayer(player, FORWARD, actionValue);
//         break;
//         case MOVE_BACKWARD:
//             mapManager.movePlayer(player, BACKWARD, actionValue);
//         break;
//         case ADD_FOOD:
//             resourceManager.addResourcesToBoathold(player, std::move(foodResource), actionValue);
//         break;
//         case ADD_GOLD:
//             resourceManager.addResourcesToBoathold(player, std::move(goldResource), actionValue);
//         break;
//         case ADD_CANONS:
//             resourceManager.addResourcesToBoathold(player, std::move(canonResource), actionValue);
//         break;

//         default:
//             break;
//     }
// }


// }

