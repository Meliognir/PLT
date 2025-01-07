/*
#include "AbstractService.h"
#include "ServiceException.h"
#include <iostream>

using namespace server;
using namespace std;

AbstractService::AbstractService(std::string pattern)
{
    this->pattern = pattern;
}

AbstractService::~AbstractService() {
    
}
const std::string& AbstractService::getPattern() const {
    return this->pattern;
}

HttpStatus AbstractService::get (Json::value* out, int id)  {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::put (Json::value* in, int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::post (Json::value* out,  Json::value* in) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}

HttpStatus AbstractService::remove (int id) {
    throw ServiceException(HttpStatus::NOT_IMPLEMENTED,"Not Implemented");
}
*/