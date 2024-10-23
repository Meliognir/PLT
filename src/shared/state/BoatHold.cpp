#include "BoatHold.h"
#include <iostream>

namespace state {

BoatHold::BoatHold(){}

BoatHold::~BoatHold(){
}

void BoatHold::addResource(std::unique_ptr<Resources> newResource, int amount) {
    if(resource==nullptr) {
        //Si boathold est vide, on peut ajouter la ressource
        resource= std::move(newResource);
        quantity = std::min(amount,6);
        std::cout<<"Added "<<quantity<< " " << resource->getType() << "(s).\n";
    } else {
        std::cout<< "Boathold already contains " <<quantity<< " " << resource->getType() << "(s).\n";
    }
}

bool BoatHold::isEmpty() {
    return resource!=nullptr;
}

int BoatHold::getQuantity() {
    return quantity;
}

std::string BoatHold::getResourceType() {
    return resource==nullptr ? resource->getType() : "None";
}

void BoatHold::showContents() {
    if (resource!=nullptr) {
        std::cout<<"Contains "<< quantity<<" " << resource-> getType() << "(s).\n";
    }else {
        std::cout<< "Boathoald is empty.\n";
    }
}

}