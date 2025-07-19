#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

class Game {
private:
    // This object is not copyable -> the assignment (=) operator is deleted. We have to inline the constructor call
    sf::RenderWindow window; 
    sf::Event e;

    void update();
    void fixedUpdate();
    void draw();

public:
    void start();
    Game(sf::Vector2i initialScreenSize, std::string gameName);
    ~Game();
};
