#include "Renderer.h"
#include <cmath>
#include <vector>
#include <iostream>
#define PI 3.14159265358979323846
#define WIDTHFAC 1.0
#define HEIGHTFAC 1.0

void render::Renderer::renderBackground(sf::RenderWindow &window){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../src/boardGameData/BackgroundJamaicaPLT.png")) {
        std::cerr << "Error loading BackgroundJamaicaPLT.png!" << std::endl;
        return;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(windowWidth) / backgroundTexture.getSize().x,
        static_cast<float>(windowHeight) / backgroundTexture.getSize().y
    );
    window.draw(backgroundSprite);
}
// beach tileset 576 * 288
void render::Renderer::renderMap(sf::RenderWindow &window, const state::Map &map){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;

    float globalScale = std::min(desktopMode.width, desktopMode.height)/2;
    int mapSize = map.getSize();          // Nombre total de tuiles
    float mapScale = 1/((float)mapSize);
    sf::Vector2f center(windowWidth/3.1f, windowHeight/2.05f);        // Centre du cercle (positionné à gauche dans la fenêtre)
    
    // Rayon du cercle
    float radius = globalScale/1.7f;
    float angleStep = 2 * PI * mapScale;   // Angle entre chaque tuile

    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf");   

    sf::Texture beachTileset;
    if (!beachTileset.loadFromFile("../src/boardGameData/Beach_Tileset.png")) {
        std::cerr << "Error loading Beach_Tileset.png!" << std::endl;
        return;
    }
    sf::Texture portRoyal;
    if (!portRoyal.loadFromFile("../src/boardGameData/PortRoyal.png")) {
        std::cerr << "Error loading PortRoyal.png!" << std::endl;
        return;
    }
    sf::Texture resourceTexture;
    if (!resourceTexture.loadFromFile("../src/boardGameData/CardSprSheet.png")) {
        std::cerr << "Error loading resource texture!" << std::endl;
        return;
    }
    sf::Texture treasureTexture;
    if (!treasureTexture.loadFromFile("../src/boardGameData/Chest.png")) {
        std::cerr << "Error loading chest texture!" << std::endl;
        return;
    }
    sf::Sprite resourceSprite;
    sf::Sprite treasureSprite;
    resourceSprite.setTexture(resourceTexture);
    resourceSprite.setTextureRect(sf::IntRect(600,175,1,1));
    treasureSprite.setTexture(treasureTexture);
    treasureSprite.setTextureRect(sf::IntRect(8,9,22,19));


    sf::Sprite tileSprite;
    sf::Sprite portRoyalSprite;
    tileSprite.setTexture(beachTileset);
    portRoyalSprite.setTexture(portRoyal);
    int tileWidth = 96;   
    int tileHeight = 96;  

    sf::Texture sunTexture;
    sf::Texture moonTexture;
    if (!sunTexture.loadFromFile("../src/boardGameData/Sun.png")) {
        std::cerr << "Error loading sun texture!" << std::endl;
        return;
    }
    if (!moonTexture.loadFromFile("../src/boardGameData/Moon.png")) {
        std::cerr << "Error loading moon texture!" << std::endl;
        return;
    }
    sf::Sprite sunSprite;
    sunSprite.setTexture(sunTexture);
    sunSprite.setTextureRect(sf::IntRect(0, 0, 400, 400));
    sunSprite.setPosition(windowWidth/16.0f, windowHeight/14.5f);
    sunSprite.setScale(sf::Vector2f(globalScale/2100.f, globalScale/2100.f));

    sf::Sprite moonSprite;
    moonSprite.setTexture(moonTexture);
    moonSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
    moonSprite.setPosition(windowWidth/1.9f, windowHeight/12.9f);
    moonSprite.setScale(sf::Vector2f(globalScale/900, globalScale/900));
    
    // Parcourir toutes les tuiles de la carte
    for (int i = 0; i < mapSize; ++i) {
        const state::Tile* tile = map.listOfTiles[i];

        // Calcul des coordonnées de la tuile sur le cercle
        float angle = i * angleStep;
        float x = center.x + (radius *1.2f) * cos(angle);
        float y = center.y + radius * sin(angle);
        
        float separatorX = center.x + radius *(1.2f) * cos(angle+angleStep/2.f);
        float separatorY = center.y + radius * sin(angle+angleStep/2.f);          

        // Tracer une ligne (rayon) entre le centre et la position de la tuile
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0.5f*(separatorX + center.x), 0.5f*(separatorY + center.y)), sf::Color::Black),
            sf::Vertex(sf::Vector2f(separatorX, separatorY), sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);
        
        // Déterminer quelle région de la texture utiliser en fonction de la ressource
        if (tile->tileResourceType == "Food") {
            tileSprite.setTextureRect(sf::IntRect(32+4*tileWidth, 96, tileWidth, tileHeight)); // Première tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            tileSprite.setScale(sf::Vector2f(globalScale/1800.f, globalScale/1800.f));
            resourceSprite.setTextureRect(sf::IntRect(30, 29, 30, 30));
            resourceSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            resourceSprite.setPosition(x+25, y+25);
            resourceSprite.setScale(sf::Vector2f(0.7f,0.7f));
            window.draw(tileSprite);
            window.draw(resourceSprite);
        } else if (tile->tileResourceType == "Gold") {
            tileSprite.setTextureRect(sf::IntRect(32+2*tileWidth, 96, tileWidth, tileHeight)); // Deuxième tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            tileSprite.setScale(sf::Vector2f(globalScale/1800.f, globalScale/1800.f));
            resourceSprite.setTextureRect(sf::IntRect(60, 29, 30, 30));
            resourceSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            resourceSprite.setPosition(x+25, y+25);
            resourceSprite.setScale(sf::Vector2f(0.7f,0.7f));
            window.draw(tileSprite);
            window.draw(resourceSprite);
        } else if (tile->treasureAvailable) {
            tileSprite.setTextureRect(sf::IntRect(32, 96, tileWidth, tileHeight)); // Troisième tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            tileSprite.setScale(sf::Vector2f(globalScale/1800.f, globalScale/1800.f));
            treasureSprite.setTextureRect(sf::IntRect(8,9,22,19));
            treasureSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            treasureSprite.setPosition(x+30, y+30);
            treasureSprite.setScale(sf::Vector2f(0.8f,0.8f));
            window.draw(tileSprite);
            window.draw(treasureSprite);
        } else if (tile->tileResourceType == "Port Royal") {
            portRoyalSprite.setTextureRect(sf::IntRect(0, 0, 192, 192)); // Par défaut (première tuile)
            portRoyalSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            portRoyalSprite.setScale(sf::Vector2f(globalScale/3600.f, globalScale/3600.f));
            portRoyalSprite.setPosition(center.x - globalScale/80.0f + radius *1.2f, center.y - globalScale/80.0f);
            window.draw(portRoyalSprite);
        } else {
            tileSprite.setTextureRect(sf::IntRect(32, 96, tileWidth, tileHeight)); // Troisième tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            tileSprite.setScale(sf::Vector2f(globalScale/1800.f, globalScale/1800.f));
            treasureSprite.setTextureRect(sf::IntRect(48, 4, 22, 24));
            treasureSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            treasureSprite.setPosition(x+30, y+30);
            treasureSprite.setScale(sf::Vector2f(0.8f,0.8f));
            window.draw(tileSprite);
            window.draw(treasureSprite);
        }


        // Ajout d'un texte pour afficher des informations sur la tuile
        int tileCost = tile->tileCost;
        if (tileCost){
            sf::Text tileText;
            tileText.setFont(font);
            tileText.setString(std::to_string(tileCost));  
            tileText.setCharacterSize(14);
            tileText.setFillColor(sf::Color::Black);
            tileText.setPosition(x - 10, y - 10);

            window.draw(tileText);
        }
    }
    window.draw(sunSprite);
    window.draw(moonSprite);
}

void render::Renderer::renderPlayers(sf::RenderWindow &window, const std::vector<state::Player *> &players, const state::Map &map){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    float globalScale = std::min(desktopMode.width, desktopMode.height)/2;
    sf::Vector2f center(windowWidth/3.1f, windowHeight/2.05f);        // Centre du cercle (positionné à gauche dans la fenêtre)

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


//old version :
/*
    for (size_t i = 0; i < players.size(); ++i) {
        const auto& player = players[i];
        int playerPosition = player->getPosition();  // Position du joueur (index de la tuile)
        int mapSize = map.getSize();
        if (playerPosition < 0){
            playerPosition = mapSize-1 - (-playerPosition)%mapSize;
        }
        else if (playerPosition >= mapSize){
            playerPosition = playerPosition%mapSize;
        } 
        // Vérifier si la position est valide dans la carte
        if (playerPosition >= 0 && playerPosition < static_cast<int>(map.listOfTiles.size())) {
            // Calculer la position de la tuile correspondante

            float mapScale = 1/((float)mapSize);
            
            // Rayon du cercle
            float radius = globalScale/2;
            float angleStep = 2 * PI * mapScale;   // Angle entre chaque tuile


            float angle = playerPosition * angleStep;
            float x = center.x + radius *(1.33f+ 0.05f*i) * cos(angle);
            float y = center.y + radius * (1.05f+ 0.05f*i) * sin(angle);

            // Créer et configurer le sprite
            sf::Sprite playerSprite;
            playerSprite.setTexture(playerTexture);
            playerSprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
            playerSprite.setOrigin(spriteWidth/2, spriteHeight/2);
            playerSprite.setScale(sf::Vector2f(1.f, 1.f));
            playerSprite.setPosition(x, y);

            // Créer et configurer le texte pour le nom du joueur
            sf::Text playerNameText;
            playerNameText.setFont(font);
            playerNameText.setString(player->getName());  
            playerNameText.setCharacterSize(16);
            playerNameText.setFillColor(playerColors[i % playerColors.size()]);  
            playerNameText.setStyle(sf::Text::Bold);
            playerNameText.setPosition(x - spriteWidth / 2 - 10, y + spriteHeight / 2 - 10);  // Position sous le sprite

            window.draw(playerSprite);
            window.draw(playerNameText);
        }
    }
    */
    // In this old version, the code was cleaner, but the usernames were sometimes hidden by the boats

    for (size_t i = 0; i < players.size(); ++i) {
        const auto& player = players[i];
        int playerPosition = player->getPosition();  // Position du joueur (index de la tuile)
        int mapSize = map.getSize();
        if (playerPosition < 0){
            playerPosition = mapSize-1 - (-playerPosition)%mapSize;
        }
        else if (playerPosition >= mapSize){
            playerPosition = playerPosition%mapSize;
        } 
        // Vérifier si la position est valide dans la carte
        if (playerPosition >= 0 && playerPosition < static_cast<int>(map.listOfTiles.size())) {
            // Calculer la position de la tuile correspondante

            float mapScale = 1/((float)mapSize);
            
            // Rayon du cercle
            float radius = globalScale/1.85f;
            float angleStep = 2 * PI * mapScale;   // Angle entre chaque tuile

            float angle = playerPosition * angleStep;
            /*
            float x = center.x + radius *(1.33f+ 0.05f*i) * cos(angle);
            float y = center.y + radius * (1.05f+ 0.05f*i) * sin(angle);
            */

            float x = center.x + radius *(1.15f - 0.11f*i) * cos(angle);
            float y = center.y + radius * (0.95f - 0.11f*i) * sin(angle);  

            // Créer et configurer le sprite
            sf::Sprite playerSprite;
            playerSprite.setTexture(playerTexture);
            playerSprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
            playerSprite.setOrigin(spriteWidth/2, spriteHeight/2);
            playerSprite.setScale(sf::Vector2f(1.f, 1.f));
            playerSprite.setPosition(x, y);
            
            window.draw(playerSprite);
        }
    }

    for (size_t i = 0; i < players.size(); ++i) {
        const auto& player = players[i];
        int playerPosition = player->getPosition();  // Position du joueur (index de la tuile)
        int mapSize = map.getSize();
        if (playerPosition < 0){
            playerPosition = mapSize-1 - (-playerPosition)%mapSize;
        }
        else if (playerPosition >= mapSize){
            playerPosition = playerPosition%mapSize;
        } 
        // Vérifier si la position est valide dans la carte
        if (playerPosition >= 0 && playerPosition < static_cast<int>(map.listOfTiles.size())) {
            // Calculer la position de la tuile correspondante

            float mapScale = 1/((float)mapSize);
            
            // Rayon du cercle
            float radius = globalScale/1.9f;
            float angleStep = 2 * PI * mapScale;   // Angle entre chaque tuile

            float angle = playerPosition * angleStep;
            /*
            float x = center.x + radius *(1.33f+ 0.05f*i) * cos(angle);
            float y = center.y + radius * (1.05f+ 0.05f*i) * sin(angle);
            */

            float x = center.x + radius *(1.15f - 0.15f*i) * cos(angle);
            float y = center.y + radius * (0.95f - 0.15f*i) * sin(angle);  


            // Créer et configurer le texte pour le nom du joueur
            sf::Text playerNameText;
            playerNameText.setFont(font);
            playerNameText.setString(player->getName());  
            playerNameText.setCharacterSize(16);
            playerNameText.setFillColor(playerColors[i % playerColors.size()]);  
            playerNameText.setStyle(sf::Text::Bold);
            playerNameText.setPosition(x - spriteWidth / 2 - 10, y + spriteHeight / 2 - 10);  // Position sous le sprite

            window.draw(playerNameText);
        }
    }
}

void render::Renderer::renderDice(sf::RenderWindow &window, int dayDie, int nightDie){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
    sf::Texture diceTexture;
    if (!diceTexture.loadFromFile("../src/boardGameData/DiceSprSheetX128.png")) {
        std::cerr << "Error loading dice texture!" << std::endl;
        return;
    }
    const int diceFaceSize = 128;  
    sf::Sprite dayDieSprite;
    sf::Sprite nightDieSprite;

    sf::Vector2f dayDiePosition(windowWidth/7.3f, windowHeight/20.0f);   
    sf::Vector2f nightDiePosition(windowWidth/2.5, windowHeight/20.0f); 

    if (dayDie > 0) {
        dayDieSprite.setTexture(diceTexture);
        dayDieSprite.setTextureRect(sf::IntRect((dayDie - 1) * diceFaceSize, 0, diceFaceSize, diceFaceSize));
        dayDieSprite.setPosition(dayDiePosition);
        window.draw(dayDieSprite);
    } 
    else {
        sf::RectangleShape dayDieRect(sf::Vector2f(diceFaceSize, diceFaceSize));
        dayDieRect.setPosition(dayDiePosition);
        dayDieRect.setFillColor(sf::Color(128, 128, 128)); 
        window.draw(dayDieRect);
    }
    if (nightDie > 0) {
        nightDieSprite.setTexture(diceTexture);
        nightDieSprite.setTextureRect(sf::IntRect((nightDie - 1) * diceFaceSize, 0, diceFaceSize, diceFaceSize));
        nightDieSprite.setPosition(nightDiePosition);
        window.draw(nightDieSprite);
    } 
    else {
        sf::RectangleShape nightDieRect(sf::Vector2f(diceFaceSize, diceFaceSize));
        nightDieRect.setPosition(nightDiePosition);
        nightDieRect.setFillColor(sf::Color(128, 128, 128)); 
        window.draw(nightDieRect);
    }
}

void render::Renderer::renderCard(sf::RenderWindow &window, int cardID){
    sf::Texture cardTexture;
    if (!cardTexture.loadFromFile("../src/boardGameData/CardSprSheet.png")) {
        std::cerr << "Error loading card texture!" << std::endl;
        return;
    }

    sf::Sprite cardSprite;
    cardSprite.setTexture(cardTexture);

    int cardWidth = 68;  
    int cardHeight = 28; 

    // Déterminer quelle région de la texture utiliser en fonction de cardID
    if (cardID >= 0 && cardID < 11) {
      cardSprite.setTextureRect(sf::IntRect(cardID * cardWidth / 2, 0, cardWidth, cardHeight));
    } else {
        std::cerr << "Invalid cardID: " << cardID << std::endl;
        return;
    }
    // Positionner la carte au centre de la fenêtre
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;

    cardSprite.setPosition((windowWidth - cardWidth) / 2.0f, (windowHeight - cardHeight) / 2.0f);
    cardSprite.setScale(sf::Vector2f(2.f, 2.f));
    window.draw(cardSprite);
}

void render::Renderer::renderHand(sf::RenderWindow &window, const std::vector<int>& handCards) {
    sf::Texture cardTexture;
    if (!cardTexture.loadFromFile("../src/boardGameData/CardSprSheet.png")) {
        std::cerr << "Error loading card texture!" << std::endl;
        return;
    }

    sf::Sprite cardSprite;
    cardSprite.setTexture(cardTexture);

    int cardWidth = 68;
    int cardHeight = 28;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;

    // Positionnement des cartes
    float startX = windowWidth / 7.5f; 
    float y = 8.3f * windowHeight/10.f;
    for (size_t i = 0; i < handCards.size() && i < 3; ++i) {
        int cardID = handCards[i];
        // Déterminer la région de la texture
        if (cardID >= 0 && cardID < 11) {
            cardSprite.setTextureRect(sf::IntRect(cardID * cardWidth /2, 0, cardWidth, cardHeight));
        } else {
            std::cerr << "Invalid cardID: " << cardID << std::endl;
            continue;
        }
        cardSprite.setPosition(startX + i * 2 * (cardWidth + 20), y);
        cardSprite.setScale(sf::Vector2f(2.f, 2.f));
        window.draw(cardSprite);
    }
}

void render::Renderer::renderBoatholds(sf::RenderWindow &window, state::Player *player, int offset){
    sf::Font font;
    font.loadFromFile("../src/boardGameData/Arial.ttf"); 
    sf::Texture boatholdTexture;
    if (!boatholdTexture.loadFromFile("../src/boardGameData/CardSprSheet.png")) {
        std::cerr << "Error loading card texture!" << std::endl;
        return;
    }
    std::vector<state::BoatHold *> boatholds = player->getBoatHolds();
    int boatHoldCount = boatholds.size();
    sf::Sprite boatholdSprite;
    sf::Sprite resourceSprite;
    boatholdSprite.setTexture(boatholdTexture);
    resourceSprite.setTexture(boatholdTexture);
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;

    int i;
    sf::Text quantityText;
    quantityText.setFont(font);    
    quantityText.setCharacterSize(20);
    quantityText.setFillColor(sf::Color::Red);

    for (i = 0; i<boatHoldCount; i++){
        boatholdSprite.setTextureRect(sf::IntRect(530,0, 90, 90));
        boatholdSprite.setPosition(0.7f * windowWidth +i*windowWidth/36.f, 0.2f * windowHeight + offset); //TODO : scale
        state::BoatHold* hold = boatholds[i];
        resourceSprite.setTextureRect(sf::IntRect(600,175,1,1));
        if (hold->getResourceType()=="Food"){
            resourceSprite.setTextureRect(sf::IntRect(30, 29, 30, 30));
        }
        if (hold->getResourceType()=="Gold"){
            resourceSprite.setTextureRect(sf::IntRect(60, 29, 30, 30));
        }
        if (hold->getResourceType()=="Canon"){
            resourceSprite.setTextureRect(sf::IntRect(90, 29, 30, 30));
        }
        int resQuantity = hold->getQuantity();
        resourceSprite.setPosition(0.7f * windowWidth +i*windowWidth/36.f, 0.21f * windowHeight + offset);

        window.draw(boatholdSprite);
        window.draw(resourceSprite);
        if (resQuantity) {
            quantityText.setString(std::to_string(resQuantity));  
            quantityText.setPosition(0.7f * windowWidth +(i+0.7f)*(windowWidth/36.f), 0.22f * windowHeight + offset);
            window.draw(quantityText);
        }
    }
}
