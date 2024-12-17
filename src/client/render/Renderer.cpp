#include "Renderer.h"
#include <cmath>
#include <vector>
#include <iostream>
#define PI 3.14159265358979323846
//beach tileset 576 * 288
void render::Renderer::renderMap(sf::RenderWindow &window, const state::Map &map){
    int mapSize = map.getSize();          // Nombre total de tuiles
    float radius = 200.0f;                // Rayon du cercle
    sf::Vector2f center(400, 300);        // Centre du cercle (position de la fenêtre)
    float angleStep = 2 * PI / mapSize;   // Angle entre chaque tuile

    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf");   

    // Parcourir toutes les tuiles de la carte
    for (int i = 0; i < mapSize; ++i) {
        const state::Tile* tile = map.listOfTiles[i];

        // Calcul des coordonnées de la tuile sur le cercle
        float angle = i * angleStep;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);

        // Représentation visuelle de la tuile
        sf::RectangleShape tileShape(sf::Vector2f(40, 40)); // Taille de chaque tuile
        tileShape.setOrigin(20, 20);                        // Centrer la tuile sur ses coordonnées
        tileShape.setPosition(x, y);

        // Couleur de la tuile en fonction de ses propriétés
        if (tile->tileResourceType == "Food") {
            tileShape.setFillColor(sf::Color::Green);
        } else if (tile->tileResourceType == "Gold") {
            tileShape.setFillColor(sf::Color::Yellow);
        } else if (tile->treasureAvailable) {
            tileShape.setFillColor(sf::Color::Red);
        } else {
            tileShape.setFillColor(sf::Color::Blue);
        }

        // Ajout d'un texte pour afficher des informations sur la tuile
        sf::Text tileText;
        tileText.setFont(font);
        tileText.setString(std::to_string(tile->tileCost));  
        tileText.setCharacterSize(14);
        tileText.setFillColor(sf::Color::Black);
        tileText.setPosition(x - 10, y - 10);

        // Dessiner la tuile et son texte
        window.draw(tileShape);
        window.draw(tileText);
    }
}

void render::Renderer::renderPlayers(sf::RenderWindow &window, const std::vector<state::Player *> &players, const state::Map &map){
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../src/boardGameData/Boats.png")) {
        std::cerr << "Error loading player texture!" << std::endl;
        return;
    }
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 

    std::vector<sf::Color> playerColors = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color::Magenta,
        sf::Color::Cyan
    };

    // Paramètres pour le sprite
    int spriteWidth = 32;  // Largeur d'une image 
    int spriteHeight = 32; // Hauteur d'une image 

    for (size_t i = 0; i < players.size(); ++i) {
        const auto& player = players[i];
        int playerPosition = player->getPosition();  // Position du joueur (index de la tuile)

        // Vérifier si la position est valide dans la carte
        if (playerPosition >= 0 && playerPosition < map.listOfTiles.size()) {
            // Calculer la position de la tuile correspondante
            float angleStep = 2 * PI / map.getSize();   // Angle entre chaque tuile
            float angle = playerPosition * angleStep;
            float radius = 200.0f;                     // Même rayon que dans renderMap
            sf::Vector2f center(400, 300);             // Centre de la carte

            float x = center.x + radius * cos(angle);
            float y = center.y + radius * sin(angle);

            // Créer et configurer le sprite
            sf::Sprite playerSprite;
            playerSprite.setTexture(playerTexture);
            playerSprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
            playerSprite.setOrigin(spriteWidth / 2, spriteHeight / 2);
            playerSprite.setPosition(x, y);

            // Créer et configurer le texte pour le nom du joueur
            sf::Text playerNameText;
            playerNameText.setFont(font);
            playerNameText.setString(player->getName());  
            playerNameText.setCharacterSize(16);
            playerNameText.setFillColor(playerColors[i % playerColors.size()]);  
            playerNameText.setStyle(sf::Text::Bold);
            playerNameText.setPosition(x - spriteWidth / 2, y + spriteHeight / 2 + 5);  // Position sous le sprite

            // Dessiner le sprite et le nom du joueur
            window.draw(playerSprite);
            window.draw(playerNameText);
        }
    }
}
