#include "ServiceException.h"

using namespace server;


ServiceException::ServiceException (HttpStatus status, std::string msg):msg(msg),status_value(status){
}

HttpStatus ServiceException::status()
{
    return status_value;
}
