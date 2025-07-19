#pragma once
#include "game.hpp"
#include "../game/player/planet.hpp"
#include "../game/enemy/enemy_manager.hpp"

void Game::start() {

    // TODO: Remove these from the game onto a dedicated class/declared variables
    sf::Clock deltaTimeClock;
    Planet player(20.f, 100, (sf::Vector2f)window.getSize());
    EnemyManager enemyManager(100, (sf::Vector2f)window.getSize(), player);
    float deltaTime;

    while (window.isOpen())
    {
        // Capture delta time
        deltaTime = deltaTimeClock.restart().asSeconds();

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
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

        // Run updates
        player.update(deltaTime);
        enemyManager.update(deltaTime);

        // Clear the window
        window.clear(sf::Color::Black);

        // draw
        player.draw(window);
        enemyManager.draw(window);

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


