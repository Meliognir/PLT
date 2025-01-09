#include "HUD.h"
#define WIDTHFAC 1.0
#define HEIGHTFAC 1.0

void render::HUD::askGamemode(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/50);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Dans quel mode souhaitez-vous jouer ? (0 = exit, 1 = local, 2 = online, 3 = duel)");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askNumberofPlayers(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Enter the number of players (2-6): ");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askIsPlayerAI(sf::RenderWindow &window, int index){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Is Player " + std::to_string(index) + " an AI?");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askAIDifficulty(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString("What is the level of this AI ? (0, 1, 2, 3)");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askPlayerName(sf::RenderWindow &window, int index){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Enter name for player" + std::to_string(index) + ":");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askMapSize(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Enter the size of the map: ");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askDayDice(sf::RenderWindow &window, int die1, int die2, std::string playerName){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ". Choose the die that will be the die for the day. \nThe other one will be the die for the night. (1 or 2)\nDie 1 : " + std::to_string(die1) + " Die 2 : " + std::to_string(die2));  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askCard(sf::RenderWindow &window, std::string playerName){ 
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ". Choose a card, enter an index between 1 and 3:");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askPlaceResource(sf::RenderWindow &window, std::string playerName, int boatholdCount, int amount, std::string resource){ //TODO33
        sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName+"receives "+std::to_string(amount)+" "+resource+". Please choose a boathold to store this resource.\n You have "+std::to_string(boatholdCount)+" boatholds. Pick one (1-"+std::to_string(boatholdCount)+")");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askBoatholdToPay(sf::RenderWindow &window, std::string playerName, int boatholdCount, int payAmount, std::string resource){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + " has to pay " + std::to_string(payAmount) + " amount of " + resource +"\n You have " + std::to_string(boatholdCount) + " boatholds. Pick one (1-" + std::to_string(boatholdCount) + ")");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

void render::HUD::askOpponent(sf::RenderWindow &window, std::string playerName, std::vector<state::Player*> players){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ". Choose an opponent, enter an index between 1 and" + std::to_string(players.size()));  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
    int i;
    for (i=0; i<players.size(); i++){
        sf::Text playerText;
        playerText.setFont(font);
        playerText.setCharacterSize(windowWidth / 50);
        playerText.setFillColor(sf::Color::Black);
        playerText.setString(std::to_string(i + 1) + ": " + players[i]->getName());
        playerText.setPosition(windowWidth / 100, windowHeight / 4 + (i + 1) * windowHeight / 16);
        window.draw(playerText);
    }
}

void render::HUD::askCanonNb(sf::RenderWindow &window, std::string playerName, int availableNb){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + "You have " + std::to_string(availableNb) + " available canons. How many do you want to use ? ");  
    Text.setPosition(windowWidth/100,windowHeight/4 );
    window.draw(Text);
}

