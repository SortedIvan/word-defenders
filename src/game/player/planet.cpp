#include "SFML/Graphics.hpp"
#include "planet.hpp"
#include <iostream>

Planet::Planet(int size, int health, sf::Vector2f screenSize) {
	this->coins = 0;
	this->size = size;
	this->health = health;

	// sf::Vector2f position, float radius, sf::Color fillColor
	planetShape = Point(
		sf::Vector2f(screenSize.x / 2, screenSize.y / 2),
		size,
		sf::Color::White
	);
}

Planet::~Planet() {

}

void Planet::update(float deltaTime) {
	if (health < 0) {
		// end the game here
		std::cout << "Game over baby!" << std::endl;
	}
}

void Planet::draw(sf::RenderWindow& window) {
	planetShape.draw(window);
}

void Planet::applyDamage(int damage) {
	health -= damage;
}

void Planet::shoot() {

}

sf::Vector2f Planet::getPosition() {
	return planetShape.getPosition();
}

Point& Planet::getShape() {
	return planetShape;
}

int Planet::getSize() {
	return size;
}