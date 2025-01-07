#include "HUD.h"
#define WIDTHFAC 1.0
#define HEIGHTFAC 1.0

void render::HUD::askGamemode(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Red);
    Text.setString("Dans quel mode souhaitez-vous jouer ? (0 = exit, 1 = local, 2 = online, 3 = duel)");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}
