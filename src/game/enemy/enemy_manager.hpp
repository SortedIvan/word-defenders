#pragma once
#include "asteroid.hpp"
#include "../src/game/player/planet.hpp"
#include "../src/math_utils/generic_math.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <stack>

// Defines a rectangle shape that represents a spawn point
struct SpawnArea {
	sf::Vector2f TL;
	sf::Vector2f BR;

	sf::Vector2f getRandomPointWithinArea() {
		return GenericMath::getRandPointInRectangle(TL, BR);
	}

	SpawnArea(sf::Vector2f TL, sf::Vector2f BR) {
		this->TL = TL;
		this->BR = BR;
	}
};

class EnemyManager {
private:
	// For now, make the only type of enemies an asteroid. 
	// Gonna have to be reworked later
	int enemyIdCounter = 0;
	std::vector<std::unique_ptr<Asteroid>> enemies;
	std::unordered_map<std::string, std::vector<int>> wordToEnemyMap;
	std::stack<int> freeIds;
	int maxEnemiesSpawned = 0;
	sf::Vector2f screenDimensions;
	int generateId();
	std::vector<SpawnArea> spawnAreas;
	Planet& planet;

	void cleanUpDestroyedEnemies(std::vector<int>& enemiesToCleanUp);

public:
	EnemyManager(int maxEnemiesSpawned, sf::Vector2f screenDimensions, Planet& planet);
	void update(float deltaTime);
	void spawnEnemy();
	void draw(sf::RenderWindow& window);
};

