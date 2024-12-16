#include "Renderer.h"
#include <cmath>
#include <vector>
#define PI 3.14159265358979323846

void render::Renderer::renderMap(sf::RenderWindow &window, const state::Map &map){
    int mapSize = map.getSize();          // Nombre total de tuiles
    float radius = 200.0f;                // Rayon du cercle
    sf::Vector2f center(400, 300);        // Centre du cercle (position de la fenêtre)
    float angleStep = 2 * PI / mapSize;   // Angle entre chaque tuile

    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf");   // Assurez-vous d'avoir une police dans le chemin res/

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
        if (tile->tileResourceType == "food") {
            tileShape.setFillColor(sf::Color::Green);
        } else if (tile->tileResourceType == "gold") {
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
        tileText.setFillColor(sf::Color::White);
        tileText.setPosition(x - 10, y - 10);

        // Dessiner la tuile et son texte
        window.draw(tileShape);
        window.draw(tileText);
    }
}