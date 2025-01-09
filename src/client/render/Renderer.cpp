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
    if (!backgroundTexture.loadFromFile("../src/boardGameData/board.png")) {
        std::cerr << "Error loading board.png!" << std::endl;
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
    int mapSize = map.getSize();          // Nombre total de tuiles
    float radius = std::min(desktopMode.width, desktopMode.height)/3;
    //float radius = 400.0f;                // Rayon du cercle
    sf::Vector2f center(windowWidth/2, windowHeight/2);        // Centre du cercle (position de la fenêtre)
    float angleStep = 2 * PI / mapSize;   // Angle entre chaque tuile

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
        std::cerr << "Error loading card texture!" << std::endl;
        return;
    }
    sf::Sprite resourceSprite;
    resourceSprite.setTexture(resourceTexture);
    resourceSprite.setTextureRect(sf::IntRect(600,175,1,1));

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
    sunSprite.setPosition((windowWidth/2)-windowWidth/12, (windowHeight/2)-windowHeight/16);
    sunSprite.setScale(sf::Vector2f(0.36f, 0.36f));

    sf::Sprite moonSprite;
    moonSprite.setTexture(moonTexture);
    moonSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
    moonSprite.setPosition((windowWidth/2)+windowWidth/20, (windowHeight/2)-windowHeight/16);
    
    // Parcourir toutes les tuiles de la carte
    for (int i = 0; i < mapSize; ++i) {
        const state::Tile* tile = map.listOfTiles[i];

        // Calcul des coordonnées de la tuile sur le cercle
        float angle = i * angleStep;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);

        // Déterminer quelle région de la texture utiliser en fonction de la ressource
        if (tile->tileResourceType == "Food") {
            tileSprite.setTextureRect(sf::IntRect(32+4*tileWidth, 96, tileWidth, tileHeight)); // Première tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            resourceSprite.setTextureRect(sf::IntRect(30, 29, 30, 30));
            resourceSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            resourceSprite.setPosition(x, y);
            window.draw(tileSprite);
            window.draw(resourceSprite);
        } else if (tile->tileResourceType == "Gold") {
            tileSprite.setTextureRect(sf::IntRect(32+2*tileWidth, 96, tileWidth, tileHeight)); // Deuxième tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            resourceSprite.setTextureRect(sf::IntRect(60, 29, 30, 30));
            resourceSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            resourceSprite.setPosition(x, y);
            window.draw(tileSprite);
            window.draw(resourceSprite);
        } else if (tile->treasureAvailable) {
            tileSprite.setTextureRect(sf::IntRect(32, 96, tileWidth, tileHeight)); // Troisième tuile
            tileSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            tileSprite.setPosition(x, y);
            resourceSprite.setTextureRect(sf::IntRect(90, 29, 30, 30));
            resourceSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            resourceSprite.setPosition(x, y);
            window.draw(tileSprite);
            window.draw(resourceSprite);
        } else {
            portRoyalSprite.setTextureRect(sf::IntRect(0, 0, 192, 192)); // Par défaut (première tuile)
            portRoyalSprite.setOrigin(tileWidth / 2, tileHeight / 2);
            portRoyalSprite.setScale(sf::Vector2f(0.5f,0.5f));
            portRoyalSprite.setPosition(x-10, y-20);
            window.draw(portRoyalSprite);
        }


        // Ajout d'un texte pour afficher des informations sur la tuile
        sf::Text tileText;
        tileText.setFont(font);
        tileText.setString(std::to_string(tile->tileCost));  
        tileText.setCharacterSize(14);
        tileText.setFillColor(sf::Color::Black);
        tileText.setPosition(x - 10, y - 10);

        window.draw(tileText);
        window.draw(sunSprite);
        window.draw(moonSprite);
    }
}

void render::Renderer::renderPlayers(sf::RenderWindow &window, const std::vector<state::Player *> &players, const state::Map &map){
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int windowWidth = desktopMode.width * WIDTHFAC; 
    unsigned int windowHeight = desktopMode.height * HEIGHTFAC;
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
        int mapSize = map.getSize();
        if (playerPosition < 0){
            playerPosition = mapSize - (-playerPosition)%mapSize;
        }
        else if (playerPosition >= mapSize){
            playerPosition = playerPosition%mapSize;
        } 
        // Vérifier si la position est valide dans la carte
        if (playerPosition >= 0 && playerPosition < static_cast<int>(map.listOfTiles.size())) {
            // Calculer la position de la tuile correspondante
            float angleStep = 2 * PI / mapSize;   // Angle entre chaque tuile
            float angle = playerPosition * angleStep;
            float radius = std::min(desktopMode.width, desktopMode.height)/3;                  // Même rayon que dans renderMap
            sf::Vector2f center(windowWidth/2, windowHeight/2);             // Centre de la carte

            float x = center.x + radius * cos(angle);
            float y = center.y + radius * sin(angle);

            // Créer et configurer le sprite
            sf::Sprite playerSprite;
            playerSprite.setTexture(playerTexture);
            playerSprite.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));
            playerSprite.setOrigin(spriteWidth/2, spriteHeight/2);
            playerSprite.setScale(sf::Vector2f(2.f, 2.f));
            playerSprite.setPosition(x + 16*i - 32, y + 16*i - 32);

            // Créer et configurer le texte pour le nom du joueur
            sf::Text playerNameText;
            playerNameText.setFont(font);
            playerNameText.setString(player->getName());  
            playerNameText.setCharacterSize(16);
            playerNameText.setFillColor(playerColors[i % playerColors.size()]);  
            playerNameText.setStyle(sf::Text::Bold);
            playerNameText.setPosition(x - spriteWidth / 2 + 16*i - 32, y + spriteHeight / 2 + 5 + 16*i - 32);  // Position sous le sprite

            window.draw(playerSprite);
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

    sf::Vector2f dayDiePosition((windowWidth/2)-windowWidth/12, (windowHeight/2)+windowHeight/12);   
    sf::Vector2f nightDiePosition((windowWidth/2)+windowWidth/20, (windowHeight/2)+windowHeight/12);  

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
    float startX = (windowWidth - (7 * cardWidth)) / 2.0f; 
    float y = windowHeight - 5*cardHeight;
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

void render::Renderer::renderBoatholds(sf::RenderWindow &window, state::Player *player){
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
        boatholdSprite.setPosition(100+i*100, 300); //TODO : scale
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
        resourceSprite.setPosition(100+i*100, 300);
        quantityText.setString(std::to_string(hold->getQuantity()));  
        quantityText.setPosition(100+i*105, 320);

        window.draw(boatholdSprite);
        window.draw(resourceSprite);
        window.draw(quantityText);
    }
}
