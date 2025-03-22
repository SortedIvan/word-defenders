#pragma once
#include "SFML/Graphics.hpp"

class Point {
private:
	sf::CircleShape shape;
public:
	Point(sf::Vector2f position, float radius, sf::Color fillColor);
	void draw(sf::RenderWindow& window);
	void move(sf::Vector2f displacement);
};