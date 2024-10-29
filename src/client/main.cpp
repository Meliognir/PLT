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
// instantiates a new Game context with concrete state GameConfig
//-----------------------------
    Game *mygame = new Game(new GameConfig, nullptr);

    mygame->request1();
    mygame->request2();

    delete mygame;
    return 0;
}

int main(int argc,char* argv[])
{
    int ret;
    ret = clientcode(); // test handle 1 and 2
    return ret;
}

