#include "ResourceManager.h"

using namespace engine;

ResourceManager::ResourceManager() {}

state::BoatHold *ResourceManager::selectBoathold(state::Player *player, const std::string resourceType, size_t index){
    auto& boatHolds = player->getBoatHolds();
   if (index < 1 || index > boatHolds.size()) {
        return nullptr;  
    }
    state::BoatHold* selectedHold = boatHolds[index-1];
    int quantityToRemove = selectedHold->getQuantity();
    selectedHold->removeResource(quantityToRemove);
    return selectedHold;
}

bool engine::ResourceManager::isBoatHoldAvailable(state::Player *player, const std::string resourceType){
    auto& boatHolds = player->getBoatHolds();
    for (state::BoatHold* hold : boatHolds) {
        if (hold && !hold->hasResourceType(resourceType)) {
            return true;
        }
    }
    return false;
}

bool engine::ResourceManager::checkSameBoathold(state::Player *player, const std::string resourceType, size_t index){
    auto& boatHolds = player->getBoatHolds();
    if (index < 1 || index > boatHolds.size()) {
        return false;  
    }
    state::BoatHold* selectedHold = boatHolds[index-1];
    return selectedHold->hasResourceType(resourceType);
}

bool engine::ResourceManager::checkOccupied(state::Player *player, size_t index){
    auto& boatHolds = player->getBoatHolds();
    if (index < 1 || index > boatHolds.size()) {
        return false; 
    }
    state::BoatHold* selectedHold = boatHolds[index];
    return !selectedHold->isEmpty();
}

void ResourceManager::addResourcesToBoathold(state::Player *player, const std::string &resourceType, int amount, int skipSelection){
}

