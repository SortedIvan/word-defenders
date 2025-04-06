#include "SFML/Graphics.hpp"
#include "planet.hpp"

void Planet::update(float deltaTime) {

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