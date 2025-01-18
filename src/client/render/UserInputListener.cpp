#include "UserInputListener.h"
#include "client.h"
#include "client/InputHandler.h"
#include <iostream>
#include <mutex>

std::mutex consoleMutex;
void safePrint(const std::string &message) { //To use std::cout in several threads
    std::lock_guard<std::mutex> lock(consoleMutex);
    std::cout << "User typed :" << std::endl;
    std::cout << message << " \n" << std::flush;    
}

render::UserInputListener::UserInputListener()
{
}

void render::UserInputListener::readInput(sf::RenderWindow *window, client::Client *client)
{
    sf::Event event;
    char enteredChar;
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
                        client->inputHandler.setUserInput(userInput);
                        client->inputHandler.setWaitingInput(false);
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
                        if (client->inputHandler.getInputTypeIsString()) {
                            if (client->inputHandler.getWaitingInput() && userInput.size() < 16) {
                                userInput += enteredChar; // Add valid character
                            }
                        } else {
                            userInput = std::string(1, enteredChar);
                            client->inputHandler.setUserInput(userInput);
                            client->inputHandler.setWaitingInput(false);
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
}

