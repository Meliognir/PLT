#include "HUD.h"
#include "state.h"
#define WIDTHFAC 1.0
#define HEIGHTFAC 1.0

void highLightText(sf::RenderWindow *window, sf::Text Text){
    // Create the white box behind the text
    sf::RectangleShape background;
    sf::FloatRect textBounds = Text.getGlobalBounds();
    background.setSize(sf::Vector2f(textBounds.width + 10.f, textBounds.height + 10.f)); // padding around the text
    background.setFillColor(sf::Color::White);
    background.setPosition(textBounds.left - 5.f, textBounds.top - 5.f);
    window->draw(background);    
}

void render::HUD::askGamemode(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/27.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("What mode do you want to play ?\n(0 = exit, 1 = local, 2 = online)"/*, 3 = duel)"*/);  
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/27.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Enter the number of players (2-6): ");  
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/27.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Is Player" + std::to_string(index) + " an AI? (y/n)");  
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/27.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("What is the level of\nthis AI ? (0, 1, 2, 3)\nPress 0 to cancel.");  
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/27.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Enter name for player" + std::to_string(index) + ".");  
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/27.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Enter the size of the map\nand press enter. (from 30 to 60)");  
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/80);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ", choose a die for the day.\nThe other die will be for the night. (1 or 2)\nDie 1 : " + std::to_string(die1) + "   and   Die 2 : " + std::to_string(die2));  
    Text.setPosition(6.f*windowWidth/10.f,windowHeight/25);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/80);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ", choose a card.\nEnter an index between 1 and 3:");  
    Text.setPosition(6.f*windowWidth/10.f,windowHeight/25);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/80);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName+" receives "+std::to_string(amount)+" "+resource+". Choose a boathold to store this resource.\n(1-"+std::to_string(boatholdCount)+").");  
    Text.setPosition(6.f*windowWidth/10.f,windowHeight/25);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/80);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + " has to pay " + std::to_string(payAmount) + " amount of " + resource +".\nPick one of your boat holds (1-" + std::to_string(boatholdCount) + ")");  
    Text.setPosition(6.f*windowWidth/10.f,windowHeight/25);
    highLightText(&window, Text);
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
    Text.setCharacterSize(windowWidth/80);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ", choose an opponent.\nEnter an index between 1 and" + std::to_string(players.size()));  
    Text.setPosition(6.f*windowWidth/10.f,windowHeight/25);
    highLightText(&window, Text);
    window.draw(Text);
    size_t i;
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
    Text.setCharacterSize(windowWidth/80);
    Text.setFillColor(sf::Color::Black);
    Text.setString(playerName + ", you have " + std::to_string(availableNb) + " available canons.\nHow many do you want to use ?");  
    Text.setPosition(6.f*windowWidth/10.f,windowHeight/25);
    highLightText(&window, Text);
    window.draw(Text);
}

void render::HUD::welcomeMessage(sf::RenderWindow &window)
{
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/15.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString("Welcome to Jamaica !");  
    Text.setPosition(windowWidth/13.f,windowHeight/2.7f);
    highLightText(&window, Text);
    window.draw(Text);
}

void render::HUD::displayResults(sf::RenderWindow &window, const std::vector<state::Player *> &players, int mapSize)
{

    std::string resultsString = "";

    state::Player * winner;
    int maxScore = -50;
    int positionEnding;
    int relativePosition;
    int playerScore;
    for(state::Player * playerEnd : players) {
        positionEnding=playerEnd->getPosition();
        relativePosition = positionEnding-mapSize;
        playerScore = 0;
        for(state::BoatHold *currentBoathold : playerEnd->getBoatHolds()){
            if (currentBoathold->hasResourceType("Gold")) {
                playerScore += currentBoathold->getQuantity();
            }
        }
        if (relativePosition <= -15) {
            playerScore -= 5;
        }
        else {
            if (relativePosition == 0){
                playerScore += 15;
            }
                else{
                switch (relativePosition) {
                    case -6:
                        playerScore += 0;
                        break;
                    case -5:
                        playerScore += 1;
                        break;
                    case -4:
                        playerScore += 3;
                        break;
                    case -3:
                        playerScore += 5;
                        break;
                    case -2:
                        playerScore += 7;
                        break;
                    case -1:
                        playerScore += 10;
                        break;
                    default:
                        break;
                }
            }
        }
        //std::cout<< "Player : " << playerEnd->getName() << " has a score of : " << playerScore << "."<< std::endl;
        resultsString += "Player : " + playerEnd->getName() + " has a score of : " + std::to_string(playerScore) + ".\n";
        if(playerScore > maxScore){
            maxScore = playerScore;
            winner = playerEnd;
        }
    }
    //std::cout<< "Player : " << winner->getName() << " has won with a score of : " << maxScore << "."<< std::endl;
    resultsString += "\nPlayer : " + winner->getName() + " has won with a score of : " + std::to_string(maxScore) + ".";

    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/40.f);
    Text.setFillColor(sf::Color::Black);
    Text.setString(resultsString);
    Text.setPosition(windowWidth/10.f,windowHeight/3.f);
    highLightText(&window, Text);
    window.draw(Text);
}
