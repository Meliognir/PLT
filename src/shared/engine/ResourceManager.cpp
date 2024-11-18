#include "ResourceManager.h"

using namespace engine;

ResourceManager::ResourceManager() {}

state::BoatHold *ResourceManager::selectBoathold(state::Player &player, const std::string resourceType, int index){
    auto& boatHolds = player.getBoatHolds();
   
        state::BoatHold* selectedHold = boatHolds[index];
        int quantityToRemove = selectedHold->getQuantity();
        selectedHold->removeResource(quantityToRemove);
        return selectedHold;
    
}

bool engine::ResourceManager::isBoatHoldAvailable(state::Player &player, const std::string resourceType){
    auto& boatHolds = player.getBoatHolds();
    bool available_holds = false;

    for (state::BoatHold* hold : boatHolds) {
        if (hold && !hold->hasResourceType(resourceType)) {
            available_holds = true;
        }
    }
    return available_holds;
}

bool engine::ResourceManager::checkSameBoathold(state::Player &player, const std::string resourceType, int index){
    auto& boatHolds = player.getBoatHolds();
    state::BoatHold* selectedHold = boatHolds[index];
    if (selectedHold->hasResourceType(resourceType)) {
        return true;
    }
    return false;
}

bool engine::ResourceManager::checkOccupied(state::Player &player, int index){
    auto& boatHolds = player.getBoatHolds();
    state::BoatHold* selectedHold = boatHolds[index];
    return !selectedHold->isEmpty();
}

void ResourceManager::addResourcesToBoathold(state::Player &player, const std::string &resourceType, int amount, int skipSelection){
}

