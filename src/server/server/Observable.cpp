#include "Observable.h"
#include <algorithm>
#include <iostream>

std::vector<server::SObserver*> server::Observable::observers;

void server::Observable::addObserver(SObserver *observer){
    observers.push_back(observer);
}

void server::Observable::removeObserver(SObserver *observer){
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void server::Observable::notifyObservers(const std::string& eventType, const std::string& data){
    for (SObserver* observer : observers) {
        //std::cout << "obs update" << std::endl;
        observer->update(eventType, data);
    }
    //std::cout << "success update obs" << std::endl;
}