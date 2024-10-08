//
// Created by Dru on 10/7/2024.
//

#include "View.h"
#include <iostream>

void View::drawQueens(sf::RenderWindow& window, const Body& body, int solutionIndex) {
    const auto& solutions = body.getSolutions();
    if (solutionIndex < 0 || solutionIndex >= solutions.size()) return;

    const auto& solution = solutions[solutionIndex];
    float squareSize = 50.0f; // Size of each square on the board

    for (size_t col = 0; col < solution.size(); ++col) {
        int row = solution[col];
        sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
        square.setPosition(col * squareSize, row * squareSize);
        square.setFillColor(sf::Color::Green); // Color for the queen's square
        window.draw(square);

        // Draw the queen
        sf::CircleShape queen(squareSize / 4); // Circle to represent the queen
        queen.setFillColor(sf::Color::Red);
        queen.setPosition(col * squareSize + squareSize / 4, row * squareSize + squareSize / 4);
        window.draw(queen);
    }
}

void View::drawSolutionCount(sf::RenderWindow& window, int currentSolution, int totalSolutions) {
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return;
    }

    sf::Text solutionText;
    solutionText.setFont(font);
    solutionText.setString("Solution " + std::to_string(currentSolution + 1) + " of " + std::to_string(totalSolutions));
    solutionText.setCharacterSize(24);
    solutionText.setFillColor(sf::Color::White);
    solutionText.setPosition(10, 10); // Position it on the window

    window.draw(solutionText); // Draw the text on the window
}
