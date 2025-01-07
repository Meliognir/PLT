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

void render::HUD::askNumberofPlayers(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Red);
    Text.setString("Enter the number of players (2-6): ");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askIsPlayerAI(sf::RenderWindow &window, int index){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Red);
    Text.setString("Is Player " + std::to_string(index) + " an AI?");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askAIDifficulty(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Red);
    Text.setString("What is the level of this AI ? (0, 1, 2, 3)");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askPlayerName(sf::RenderWindow &window, int index){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Red);
    Text.setString("Enter name for player" + std::to_string(index) + ":");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askMapSize(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Red);
    Text.setString("Enter the size of the map: ");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askDayDice(sf::RenderWindow &window, int die1, int die2){
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

void render::HUD::askCard(sf::RenderWindow &window){
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

void render::HUD::askPlaceResource(sf::RenderWindow &window){
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

void render::HUD::askBoatholdToPay(sf::RenderWindow &window){
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

void render::HUD::askOpponent(sf::RenderWindow &window){
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
