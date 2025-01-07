/*#include "UserService.h"
#include "ServiceException.h"
#include <memory>

using namespace server;
using namespace std;

UserService::UserService(Game &game) : AbstractService("/player"), game(game)
{
}

HttpStatus UserService::get(Json::Value &out, int id)
{
    if(id == -1){
        Json::Value playersArray(Json::arrayValue);
        for(auto& p : game.getPlayers()){
            Json::Value inArray(Json::arrayValue);
            inArray.append(p.first);
            inArray.append(p.second->name);
            playersArray.append(inArray);
        }
        out["players"] = playersArray;
        return HttpStatus::OK;
    }
    Player *player = game.getPlayerById(id);
    if (!player)
        throw ServiceException(HttpStatus::NOT_FOUND, "Invalid player id");
    out["name"] = player->name;
    out["free"] = player->free;
    out["playerNumber"] = (game.getPlayers().begin()->first == id) ? 1 : 2;
    return HttpStatus::OK;
}

HttpStatus UserService::put(Json::Value &in, int id)
{
    state::Player *player = game.getPlayerById(id);
    if (!player)
        throw ServiceException(HttpStatus::NOT_FOUND, "Invalid player id");
    
    unique_ptr<Player> playermod(new state::Player(*player));
    if (in.isMember("name"))
        playermod->name = in["name"].asString();
    if (in.isMember("free"))
        playermod->free = in["free"].asBool();
    game.modifyPlayer(id, std::move(playermod));
    return HttpStatus::NO_CONTENT;
}

HttpStatus UserService::post(Json::Value &out, Json::Value &in)
{
    if(in.isMember("player_id"))
        return put(in, in["player_id"].asInt());
    if (game.getPlayers().size() >= 2)
        throw ServiceException(HttpStatus::OUT_OF_RESOURCES, "Without free places to join");
    std::string name = in["name"].asString();
    bool free = in["free"].asBool();
    state::Player new_player(name, free);
    std::unique_ptr<state::Player> ptr_player(new state::Player(new_player));
    out["id"] = game.addPlayer(move(ptr_player));
    return HttpStatus::CREATED;
}

HttpStatus UserService::remove(int id)
{
    state::Player *player = game.getPlayerById(id);
    
    if (!player)
        throw ServiceException(HttpStatus::NOT_FOUND, "Invalid player id");
    
    game.removePlayer(id);
    return HttpStatus::NO_CONTENT;
}*/
