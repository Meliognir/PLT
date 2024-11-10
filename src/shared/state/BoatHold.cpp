#include "BoatHold.h"
#include <iostream>

namespace state {

BoatHold::BoatHold(){}

BoatHold::~BoatHold(){
}

void BoatHold::addResource(std::unique_ptr<Resources> newResource, int amount) {
    if(resource == nullptr) {
        //Si boathold est vide, on peut ajouter la ressource
        resource= std::move(newResource);
        quantity = std::min(amount,6);
        std::cout<<"Added "<<quantity<< " " << resource->getType() << "(s).\n";
    } else {
        std::cout<< "Boathold already contains " <<quantity<< " " << resource->getType() << "(s).\n";
    }
}

bool BoatHold::isEmpty() {
    return resource==nullptr;
}

int BoatHold::getQuantity() {
    return quantity;
}

std::string BoatHold::getResourceType() {
    return resource != nullptr ? resource->getType() : "None";
}

void BoatHold::showContents() {
    if (resource != nullptr) {
        std::cout<<"Contains "<< quantity<<" " << resource-> getType() << "(s).\n";
    }else {
        std::cout<< "Boathold is empty.\n";
    }
}

bool BoatHold::hasResourceType(std::string type){
    return resource && resource->getType() == type;
}

void BoatHold::removeResource(int amount){
    if (resource == nullptr) {
        std::cout << "Le BoatHold est déjà vide. Aucune ressource à retirer.\n";
        return;
    }
    if (amount >= quantity) {
        std::cout << "Retrait de toutes les ressources de type " << resource->getType() << ".\n";
        resource = nullptr;  
        quantity = 0;
    } else {
        quantity -= amount;
        std::cout << "Retiré " << amount << " " << resource->getType() << "(s). Il en reste " << quantity << ".\n";
    }
}
}