#include "SFML/Graphics.hpp"
#include "../src/generic_constructs/point.hpp"

class Planet {
private:
	int size;
	int health;
	int coins;

	// Keep shape as point for now
	Point planetShape;

public:
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void applyDamage(int damage);
	void shoot();
	sf::Vector2f getPosition();
	Point& getShape();
	int getSize(); // in this case, this is the radius of the planet
};