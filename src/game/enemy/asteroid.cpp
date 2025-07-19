#include <string>
#include <iostream>
#include "asteroid.hpp"
#include "../../math_utils/vec_math.hpp"
#include "../../math_utils/geometry_math.hpp"
#include "../../general_utils/vec_utils.hpp"

bool asteroidCollides(sf::Vector2f trajectoryDirection, int size, Planet& target, sf::Vector2f asteroidCenter) {
	sf::Vector2f pointThatCanCollide = (trajectoryDirection * (float)size) + asteroidCenter;
	return GeometryMath::checkCircleContainsPoint(target.getSize(), target.getPosition(), pointThatCanCollide);
}

Asteroid::Asteroid(int id, int size, int health, int speed, int coinRewardUponDestroying,
	std::string wordToDestroy, sf::Vector2f spawnPosition, Planet& target, int damage) 
	: target(target) {

	this->id = id;
	this->size = size;
	this->speed = speed;
	this->coinRewardUponDestroying = coinRewardUponDestroying;
	this->health = health;
	this->wordToDestroy = wordToDestroy;
	this->damage = damage;
	
	destroyed = false;
	trajectoryDirection = VecMath::normalize(target.getPosition() - spawnPosition);
	
	std::cout << "Position: "; VecUtils::printSfVec(spawnPosition);
	std::cout << "Trajectory: "; VecUtils::printSfVec(trajectoryDirection);

	asteroidShape = Point(spawnPosition, size, sf::Color::Red);
	asteroidShape.getCircleShape().setOrigin(sf::Vector2f(size / 2, size / 2));
}

void Asteroid::update(float deltaTime) {
	// first, check if the asteroid has reached the target -> thus deal damage
	checkForTargetCollision();

	// perform any other asteroid updates here
	if (!destroyed) {
		moveTowardsTarget(deltaTime);
	}
}

void Asteroid::draw(sf::RenderWindow& window) {
	asteroidShape.draw(window);
}

Asteroid::~Asteroid() {
	// Destroy any asteroid related items here
}

// we already store the position in the point class, no need to have it in the asteroid itself as well
void Asteroid::moveTowardsTarget(float deltaTime) {
	if (debugEnabled) {
		sf::Vector2f asteroidPos = asteroidShape.getPosition();
		sf::Vector2f asteroidMovementVec = trajectoryDirection * deltaTime * (float)speed;

		std::cout << "======================" << std::endl;
		std::cout << "Asteroid pos:"; VecUtils::printSfVec(asteroidPos);
		std::cout << "Move vec:"; VecUtils::printSfVec(asteroidMovementVec);
	}

	asteroidShape.move(
		trajectoryDirection * deltaTime * ((float)speed * 100)
	);


}

void Asteroid::checkForTargetCollision() {
	// first, calculate the point which is facing towards the target
	// we can do this by taking the trajectory direction vector and multiplying it by the radius
	// this way we scale it to the edge of the asteroid

	if (destroyed) {
		return;
	}

	if (asteroidCollides(trajectoryDirection, size, target, asteroidShape.getPosition())) {
		target.applyDamage(damage);
		destroyed = true;
	}
}

bool Asteroid::isDead() {
	return destroyed;
}

int Asteroid::getId() {
	return id;
}

std::string Asteroid::getWordToDestroy() {
	return wordToDestroy;
}