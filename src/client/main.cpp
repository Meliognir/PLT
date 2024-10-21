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

//-----------------------
// instantiates a "Game *game" Context and sets an "initConfig" concrete state
//-----------------------

int main(int argc,char* argv[])
{

    cout << "It works !\n" << endl;

    state::Player *player0 = new state::Player(0);

    player0->setPosition(20);
    cout << "A new player was created\n" << endl;

    cout << "player is at position :" << player0->getPosition() << endl;    

    return 0;
}
