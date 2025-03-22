#include "point.hpp"

Point::Point(sf::Vector2f position, float radius, sf::Color fillColor) {
	shape = sf::CircleShape(radius);
	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(position);
	shape.setFillColor(fillColor);
}

void Point::draw(sf::RenderWindow& window) {
	window.draw(shape);
}

void Point::move(sf::Vector2f displacement) {
	shape.setPosition(shape.getPosition() + displacement);
}