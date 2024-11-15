#include <iostream>

// The following lines are here to check that SFML is installed and working
#include <SFML/Graphics.hpp>

void testSFML() {
    sf::Texture texture;
}
//end of test SFML


#include "../shared/state.h" //to use vscode tasks file instead of makefile
//#include <state.h>


using namespace std;
using namespace state;

int clientcode(){
//-----------------------------
// instantiates a new Game context and runs concrete states "GameConfig" then "Playing" functions
//-----------------------------
    Game *mygame = new Game(new GameConfigState, nullptr); //transition to GameConfig

    mygame->request1(); //initializes Players
    mygame->request2(); //transition to Playing

    mygame->request1(); //initializes Map, Players parameters
    mygame->request2(); //game loop

    delete mygame;
    return 0;
}

int main(int argc,char* argv[])
{
    int ret;
    ret = clientcode(); // test handle 1 and 2
    return ret;
}

