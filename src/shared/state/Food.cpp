//
// Created by trias on 21/10/24.
//
#include "Food.h"

namespace state {


    Food::~Food() {

    }

    std::string Food::getType() {
        std::string out = "Food";
        return out;
    }
}