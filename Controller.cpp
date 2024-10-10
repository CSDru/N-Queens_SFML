//
// Created by Dru on 10/7/2024.
//

#include "Controller.h"
#include <SFML/System.hpp>
#include <iostream>

// Constructor
Controller::Controller(int size)
        : model(size), view(size)
{
}

void Controller::run()
{
    previousMousePos = {0, 0};
    if (!model.solve())
    {
        std::cout << "No solutions found for N = " << model.getBoard().size() << std::endl;
        return;
    }

    const auto& solutions = model.getSolutions();
    size_t current = 0;
    size_t total = solutions.size();

    bool showDialog = false;
    int selectedButton = -1; // 0: Yes, 1: No

    while (view.isOpen())
    {
        // Handle all events
        std::vector<sf::Event> events = view.handleEvents();
        for (const auto& event : events)
        {
            if (event.type == sf::Event::Closed)
            {
                showDialog = true;
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (!showDialog)
                {
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        current = (current + 1) % total; // Wrap around to the first solution
                    }
                    else if (event.key.code == sf::Keyboard::Left)
                    {
                        current = (current == 0) ? total - 1 : current - 1; // Wrap around to the last solution
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        showDialog = true;
                    }
                }
                else
                {
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        selectedButton = (selectedButton + 1) % 2; // Navigate to the next button
                    }
                    else if (event.key.code == sf::Keyboard::Left)
                    {
                        selectedButton = (selectedButton - 1 + 2) % 2; // Navigate to the previous button
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        if (selectedButton == 0) // Yes: Exit the program
                        {
                            view.handleEvents(); // Clear remaining events
                            view.getWindow().close(); // Close the window
                            return;
                        }
                        else if (selectedButton == 1) // No: Close the dialog and continue
                        {
                            showDialog = false;
                        }
                    }
                    else if (event.key.code == sf::Keyboard::Escape)
                    {
                        showDialog = false; // Cancel the exit
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (showDialog && event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = view.getWindow().mapPixelToCoords(sf::Mouse::getPosition(view.getWindow()));
                    if (view.isMouseOverButton(mousePos, view.getYesButton()))
                    {
                        view.getWindow().close(); // Close the window
                        return;
                    }
                    else if (view.isMouseOverButton(mousePos, view.getNoButton()))
                    {
                        showDialog = false; // Close the dialog and continue
                    }
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePos = view.getWindow().mapPixelToCoords(sf::Mouse::getPosition(view.getWindow()));
                if(mousePos != previousMousePos)
                {
                    if (showDialog)
                    {
                        if (view.isMouseOverButton(mousePos, view.getYesButton()))
                            selectedButton = 0;
                        else if (view.isMouseOverButton(mousePos, view.getNoButton()))
                            selectedButton = 1;
                        else
                            selectedButton = -1;
                    }

                    // Update the previous mouse position
                    previousMousePos = mousePos;
                }
            }
        }

        // Draw the current solution with or without the confirmation dialog
        if (!showDialog)
        {
            view.draw(solutions[current], current, total, false, -1);
        }
        else
        {
            view.draw(solutions[current], current, total, true, selectedButton);
        }

        sf::sleep(sf::milliseconds(10)); // limit the loop
    }
}
