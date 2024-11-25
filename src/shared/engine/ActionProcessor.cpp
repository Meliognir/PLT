#include "ActionProcessor.h"
#include "../state.h"

/* -------------------------------------------- */
/* -----------Aurélien works here ------------- */
/* -------------------------------------------- */

#define DAY true
#define NIGHT false

#define FORWARD 1
#define BACKWARD -1

#define MOVE_FORWARD 0
#define MOVE_BACKWARD 1
#define ADD_FOOD 2
#define ADD_GOLD 3
#define ADD_CANONS 4


namespace engine {
void ActionProcessor::performAction(state::Player *player, state::ActionCard *actionCard)
{
    ResourceManager resourceManager;
    MapManager mapManager;
    int actionType;
    int actionValue;
    // lire l'action selon si c'est le jour ou le matin
    if (state::Game::time == DAY){
        actionType = actionCard->getDayAction();
        actionValue = state::Game::dayDie;
    }

    if (state::Game::time == NIGHT){
        actionType = actionCard->getNightAction();
        actionValue = state::Game::nightDie;
    }

    switch (actionType)
    {
    case MOVE_FORWARD:
        mapManager.movePlayer(player, FORWARD, actionValue);
        break;
    case MOVE_BACKWARD:
        mapManager.movePlayer(player, BACKWARD, actionValue);
        break;
    case ADD_FOOD:
        //resourceManager.addResourcesToBoathold(player, "food", actionValue);
        break;
    case ADD_GOLD:
        //resourceManager.addResourcesToBoathold(player, "gold", actionValue);
        break;
    case ADD_CANONS:
        //resourceManager.addResourcesToBoathold(player, "canons", actionValue);
        break;
    
    default:
        break;
    }


}

}