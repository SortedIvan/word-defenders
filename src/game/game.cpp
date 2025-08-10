#pragma once
#include "game.hpp"
#include "../game/player/planet.hpp"
#include "../game/enemy/enemy_manager.hpp"

void tryLoadFont(sf::Font& font, std::string path);
void displayGameOverText(Planet& player, sf::Text& gameOverText, sf::RenderWindow& window);
void setGameOverTextPosition(sf::Text& text, sf::RenderWindow& window);

void Game::start() {

    // TODO: Remove these from the game onto a dedicated class/declared variables
    sf::Clock deltaTimeClock;
    Planet player(20.f, 100, (sf::Vector2f)window.getSize());
    EnemyManager enemyManager(100, (sf::Vector2f)window.getSize(), player);
    float deltaTime;
    
    bool closeWindow = false;

    sf::Font font;
    tryLoadFont(font, "./8bitfont.ttf");
    sf::Text gameEndText("YOU ARE DEAD", font);
    gameEndText.setCharacterSize(50);
    setGameOverTextPosition(gameEndText, window);

    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart().asSeconds();

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            // Check if game is finished
            if (player.isDead()) {
                if (e.type == sf::Event::KeyReleased) {
                    closeWindow = true;
                    break;
                }

                continue;
            }


            if (e.type == sf::Event::TextEntered)
            {

            }

            if (e.type == sf::Event::KeyReleased) {
                switch (e.key.code) {
                    case sf::Keyboard::Space:
                        enemyManager.spawnEnemy();
                        break;
                }
            }
        }

        if (closeWindow) { break; }

        if (!player.isDead()) {
            // Run updates
            player.update(deltaTime);
            enemyManager.update(deltaTime);
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // draw
        player.draw(window);
        enemyManager.draw(window);
        
        displayGameOverText(player, gameEndText, window);

        // display
        window.display();
    }
}

Game::Game(sf::Vector2i initialScreenSize, std::string gameName)
: window(sf::VideoMode(initialScreenSize.x, initialScreenSize.y), gameName) {

}

Game::~Game() {

}

void Game::draw() {
    
}

void Game::update() {

}

void Game::fixedUpdate() {

}

void tryLoadFont(sf::Font& font, std::string path) {
    {
        if (!font.loadFromFile(path))
        {
            std::cout << "Error loading the font file" << std::endl;
            system("pause");
        }
    }
}

void displayGameOverText(Planet& player, sf::Text& gameOverText, sf::RenderWindow& window) {
    if (!player.isDead()) {
        return;
    }

    window.draw(gameOverText);
}

void setGameOverTextPosition(sf::Text& text, sf::RenderWindow& window) {
    sf::Vector2f windowSize = (sf::Vector2f)window.getSize();
    
    text.setPosition(
        (windowSize.x / 2) - (text.getCharacterSize() * text.getString().getSize()) / 3.10,
        (windowSize.y / 2) - (text.getCharacterSize() * 3)
    );
}