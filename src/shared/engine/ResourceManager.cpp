#include "ResourceManager.h"
#include <iostream>

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

int engine::ResourceManager::countResource(state::Player *player, const std::string &resourceType){
    if (!player) {
        return 0;
    }
    int total = 0;
    for (state::BoatHold* boatHold : player->getBoatHolds()) {
        if (boatHold->hasResourceType(resourceType)) {
            total += boatHold->getQuantity();
        }
    }
    return total;
}

void engine::ResourceManager::addResourcesToBoathold (state::Player *player, std::unique_ptr<state::Resources> resource, int amount, int skipSelection/* default value=0*/){
    if (!resource) {
        std::cerr << "Erreur : le pointeur resource est nul !\n";
        return;
    }

    std::string resourceType = resource->getType();
    state::BoatHold *selectedBoatHold;

    if (skipSelection){
        selectedBoatHold = player->getBoatHolds().at(skipSelection-1);
    }
    else {
        selectedBoatHold = selectBoathold(player,resourceType,6);
    }

    if (selectedBoatHold != nullptr){
        selectedBoatHold->addResource(std::move(resource), amount);
        std::cout << "Ressource ajoutée au BoatHold avec succès !\n";
    }
    else{
        selectedBoatHold = selectBoathold(player,resourceType,6);
        if (selectedBoatHold != nullptr){
            selectedBoatHold->addResource(std::move(resource), amount);
            std::cout << "Ressource ajoutée au BoatHold avec succès !\n";
        }
        else{
            std::cout << "La ressource n'a pas pu ếtre ajoutée.\n";
        }
    }
}
