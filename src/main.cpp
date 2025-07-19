#include <iostream>
#include "game/game.hpp"

int main()
{
    Game game(sf::Vector2i(1500, 900), "Test game");
    game.start();
    game.~Game();
}