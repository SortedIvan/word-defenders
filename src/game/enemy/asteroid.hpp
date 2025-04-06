#pragma once
#include <string>

#include "SFML/Graphics.hpp"
#include "../src/generic_constructs/point.hpp"
#include "../player/planet.hpp"

class Asteroid {
private:
	sf::Vector2f trajectoryDirection;
	Planet& target;

	std::string wordToDestroy;
	int size;
	int health;
	int coinRewardUponDestroying;
	int speed;
	int damage;
	bool destroyed;

	// Keep the asteroid a point/circle shape for now
	Point asteroidShape;

	void moveTowardsTarget(float deltaTime);
	void checkForTargetCollision();
public:
	Asteroid(int size, int health, int speed, int coinRewardUponDestroying,
		std::string wordToDestroy, sf::Vector2f spawnPosition, Planet& target, int damage);
	~Asteroid();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
};