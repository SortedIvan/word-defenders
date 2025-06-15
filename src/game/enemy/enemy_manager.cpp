#include "enemy_manager.hpp"
#include "../src/general_utils/vec_utils.hpp"

#define SPAWN_AREA_DISTANCE_FROM_SCREEN 150.f
#define WIDTH_HEIGHT_OF_SPAWN_AREAS 150.

EnemyManager::EnemyManager(int maxEnemiesSpawned, sf::Vector2f screenDimensions, Planet& planet) : planet(planet) {
	this->maxEnemiesSpawned = maxEnemiesSpawned;
	this->screenDimensions = screenDimensions;

	// 4 spawn areas, all 150 pixels away from the screen bounds
	// 150.f for the height for the ones top & right, 150.f for the width of left & right
	spawnAreas = std::vector<SpawnArea>{
		// Top of screen
		SpawnArea(
			sf::Vector2f(0,-(SPAWN_AREA_DISTANCE_FROM_SCREEN + WIDTH_HEIGHT_OF_SPAWN_AREAS)),
			sf::Vector2f(screenDimensions.x, -(SPAWN_AREA_DISTANCE_FROM_SCREEN))
		),
		// Bottom of screen
		SpawnArea(
			sf::Vector2f(0, screenDimensions.y + SPAWN_AREA_DISTANCE_FROM_SCREEN),
			sf::Vector2f(screenDimensions.x, SPAWN_AREA_DISTANCE_FROM_SCREEN + WIDTH_HEIGHT_OF_SPAWN_AREAS)
		),
		// Right of screen
		SpawnArea(
			sf::Vector2f(screenDimensions.x + SPAWN_AREA_DISTANCE_FROM_SCREEN, 0),
			sf::Vector2f(screenDimensions.x + SPAWN_AREA_DISTANCE_FROM_SCREEN + WIDTH_HEIGHT_OF_SPAWN_AREAS, screenDimensions.y)
		),
		// Left of screen
		SpawnArea(
			sf::Vector2f(-(SPAWN_AREA_DISTANCE_FROM_SCREEN + WIDTH_HEIGHT_OF_SPAWN_AREAS), 0),
			sf::Vector2f(-SPAWN_AREA_DISTANCE_FROM_SCREEN, screenDimensions.y)
		)
	};
}

int EnemyManager::generateId() {
	if (!freeIds.empty()) {
		int top = freeIds.top();
		freeIds.pop();
		return top;
	}

	return enemyIdCounter++;
}

void EnemyManager::update(float deltaTime) {	
	std::vector<int> enemiesToCleanUp;

	for (int i = 0; i < enemies.size(); ++i) {
		Asteroid* enemy = enemies[i].get();
		
		if (enemy->isDead()) {
			enemiesToCleanUp.push_back(enemy->getId());
		}
		else {
			// otherwise, run its updates
			enemy->update(deltaTime);
		}
	}
}

void EnemyManager::draw(sf::RenderWindow& window) {
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i].get()->draw(window);
	}
}

void EnemyManager::spawnEnemy() {
	// choose a random spawn area and spawn point
	int randomArea = GenericMath::getRandomInt(0, static_cast<int>(spawnAreas.size()) - 1);
	sf::Vector2f spawnPoint = spawnAreas[randomArea].getRandomPointWithinArea();

	// choose random word to be assigned to the enemy which will destroy it
	// for testing, just pick one of couple of words
	std::vector<std::string> testWords = { "hello", "world", "testing", "discombobulated" };
	std::string randomWord = testWords[GenericMath::getRandomInt(0, static_cast<int>(testWords.size()) - 1)];

	int enemyId = generateId();
	std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(
		enemyId, 20, 10, 5, 10, randomWord, spawnPoint, planet, 10
	);

	if (enemies.size() == enemyId) {
		enemies.push_back(std::move(asteroid));
	}
	else {
		// enemyId is somewhere back in the vector, we can replace nullptr with new ptr
		enemies[enemyId] = std::move(asteroid);
	}

	wordToEnemyMap[randomWord].push_back(enemyId);
}

// We have to clean up any word entries and also free up the id
void EnemyManager::cleanUpDestroyedEnemies(std::vector<int>& enemiesToCleanUp) {
	for (int i = 0; i < enemiesToCleanUp.size(); ++i) {
		Asteroid* enemy = enemies[enemiesToCleanUp[i]].get();
		const std::string wordToDestroy = enemy->getWordToDestroy();
		int enemyId = enemy->getId();
		
		// more than one enemy occurance with the same word, have to find the exact one
		if (wordToEnemyMap[wordToDestroy].size() > 1) {
			VecUtils::findAndDelete<int>(wordToEnemyMap[wordToDestroy], enemyId);
		}
		else {
			// completely delete the entry
			wordToEnemyMap.erase(wordToDestroy);
		}

		freeIds.push(enemyId);
	}
}