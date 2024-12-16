#include "AssignDice.h"

namespace engine{

AssignDice::AssignDice(int chosenDice, int otherDice) : chosenDice(chosenDice), otherDice(otherDice){
}

void const AssignDice::launchCommand(state::Game * GamePtr){
    GamePtr->dayDie = chosenDice;
    GamePtr->nightDie = otherDice;
}

AssignDice::~AssignDice(){}

}

