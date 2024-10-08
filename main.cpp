#include <SFML/Graphics.hpp>
#include <iostream>
#include "Controller.h"

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "N-Queens Problem");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("C:/Users/Dru/CLionProjects/N-Queens_SFML/fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return EXIT_FAILURE; // Exit if the font cannot be loaded
    }

    // Create controller
    Controller controller;
    controller.run();

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // Draw your game objects here
        window.display();
    }

    return 0;
}
