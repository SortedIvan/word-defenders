#include <iostream>
#include "SFML/Graphics.hpp"

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(1500, 900),
        "Word defenders");

    sf::Event e;

    // Main loop
    while (window.isOpen())
    {

        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::TextEntered)
            {

            }
        }

        // Run updates


        // Clear the window
        window.clear(sf::Color::Black);

        // draw
        // 
        // display
        window.display();
    }
}