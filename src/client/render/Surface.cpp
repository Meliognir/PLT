#include "Surface.h"
#include <iostream>
bool render::Surface::loadTextures(state::State *state, sf::Texture *tilesetTexture, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    sf::RenderWindow window(sf::VideoMode(2100, 1400), "My window");
        sf::Texture texture;
    if (!texture.loadFromFile("../src/boardGameData/board.png"))
        {
        // error...
        std::cout << "error opening map image" << std::endl;
        }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::Vector2u textureSize = texture.getSize(); // Taille de l'image
    sf::Vector2u windowSize = window.getSize();   // Taille de la fenêtre

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    sprite.setScale(scaleX, scaleY); // Appliquer l'échelle au sprite


    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type){
                // window closed
                case sf::Event::Closed:
                    window.close();
                    break;

                    // key pressed
                case sf::Event::KeyPressed:
                
                    break;

                case sf::Event::TextEntered:
                    if (event.text.unicode < 128)
                        std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                    }
                // we don't process other types of events
                default:
                    break;
            }
        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(sprite);

        // end the current frame
        window.display();
}
    return false;
}