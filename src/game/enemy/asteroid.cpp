#include <string>
#include "asteroid.hpp"
#include "../../math_utils/vec_math.hpp"
#include "../../math_utils/geometry_math.hpp"

Asteroid::Asteroid(int size, int health, int speed, int coinRewardUponDestroying,
	std::string wordToDestroy, sf::Vector2f spawnPosition, Planet& target, int damage) 
	: target(target) {

	this->size = size;
	this->speed = speed;
	this->coinRewardUponDestroying = coinRewardUponDestroying;
	this->health = health;
	this->wordToDestroy = wordToDestroy;
	this->target = target;
	this->damage = damage;
	
	destroyed = false;
	trajectoryDirection = VecMath::normalize(target.getPosition() - spawnPosition);
	asteroidShape = Point(spawnPosition, size, sf::Color::Red);
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
	asteroidShape.move(
		asteroidShape.getPosition() + (trajectoryDirection * deltaTime * (float)speed)
	);
}

void Asteroid::checkForTargetCollision() {
	// first, calculate the point which is facing towards the target
	// we can do this by taking the trajectory direction vector and multiplying it by the radius
	// this way we scale it to the edge of the asteroid

	if (destroyed) {
		return;
	}

	sf::Vector2f pointThatCanCollide = trajectoryDirection * (float)size;

	if (GeometryMath::checkCircleContainsPoint(target.getSize(), target.getPosition(), pointThatCanCollide)) {
		// we have hit the target, apply damage and destroy
		target.applyDamage(damage);
		destroyed = true;
	}
}