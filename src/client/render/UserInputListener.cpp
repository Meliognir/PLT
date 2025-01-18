#include "UserInputListener.h"
#include "client.h"
#include "client/InputHandler.h"
#include <iostream>
#include <mutex>

#define WIDTHFAC 1.0
#define HEIGHTFAC 1.0

std::mutex consoleMutex;
void safePrint(const std::string &message) { //To use std::cout in several threads
    std::lock_guard<std::mutex> lock(consoleMutex);
    std::cout << "User typed :" << std::endl;
    std::cout << message << " \n" << std::flush;    
}

render::UserInputListener::UserInputListener()
{
    userInput = "";
}

void render::UserInputListener::readInput(sf::RenderWindow *window, client::InputHandler *inputHandler)
{
    if (!inputHandler) {
        std::cerr << "Invalid input handler." << std::endl;
        return;
    }

    sf::Event event;
    char enteredChar;
    inputHandler->setShouldStartListening(false);
    while (window->pollEvent(event)) {
        switch (event.type) {
            // Window closed
            case sf::Event::Closed:
                window->close();
                break;

            // Key pressed
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Enter) {
                    if (!userInput.empty()) {
                        inputHandler->setUserInput(userInput);
                        inputHandler->setWaitingInput(false);
                        safePrint(userInput);
                        userInput.clear(); // Clear input
                    }
                } else if (event.key.code == sf::Keyboard::Backspace) {
                    if (!userInput.empty()) {
                        userInput.pop_back(); // Remove the last character
                    }
                }
                break;

            // Text entered (ASCII characters only)
            case sf::Event::TextEntered:
                if (event.text.unicode < 128) {
                    enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar != '\n' && enteredChar != '\r' && enteredChar != '\b'){
                        if (inputHandler->getInputTypeIsString()) {
                            if (inputHandler->getWaitingInput() && userInput.size() < 16) {
                                userInput += enteredChar; // Add valid character
                            }
                        } else {
                            userInput = std::string(1, enteredChar);
                            inputHandler->setUserInput(userInput);
                            inputHandler->setWaitingInput(false);
                            //safePrint(userInput);
                            userInput.clear(); // Clear input
                        }
                    }
                }
                break;

            // Mouse button pressed
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "The left button was pressed" << std::endl;
                    std::cout << "Mouse X: " << event.mouseButton.x << std::endl;
                    std::cout << "Mouse Y: " << event.mouseButton.y << std::endl;
                }
                break;

            // Default (unprocessed events)
            default:
                break;
        }
    }
    //echo(window);
}

void render::UserInputListener::echo(sf::RenderWindow *window)
{
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Blackpearl-vPxA.ttf"); 
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Text Text;
    Text.setFont(font);    
    Text.setCharacterSize(windowWidth/50);
    Text.setFillColor(sf::Color::Black);
    Text.setString(userInput);  
    Text.setPosition(8.f*windowWidth/10.f,19.f*windowHeight/20.f );
    window->draw(Text);
}
