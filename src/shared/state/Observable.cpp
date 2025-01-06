#include "Observable.h"
#include <algorithm>
#include <iostream>

std::vector<state::IObserver*> state::Observable::observers;

void state::Observable::addObserver(IObserver *observer){
    observers.push_back(observer);
}

void state::Observable::removeObserver(IObserver *observer){
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void state::Observable::notifyObservers(){
    std::cout << "attempt update obs" << std::endl;
    for (IObserver* observer : observers) {
        std::cout << "obs update" << std::endl;
        observer->update();
    }
    std::cout << "success update obs" << std::endl;
}