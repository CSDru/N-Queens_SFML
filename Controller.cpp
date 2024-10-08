//
// Created by Dru on 10/7/2024.
//

#include "Controller.h"
#include "View.h"
#include "Body.h"

Controller::Controller() : body(8), view() { // You can change the size (8) as needed

}

void Controller::run() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "N-Queens");

    int boardSize = 8; // Set your desired board size
    Body body(boardSize); // Create Body instance with the board size
    body.solve(); // This should generate the solutions

    int currentSolutionIndex = 0;
    const auto& solutions = body.getSolutions();
    int totalSolutions = solutions.size();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Handle arrow keys for solution navigation
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    currentSolutionIndex = (currentSolutionIndex - 1 + totalSolutions) % totalSolutions;
                } else if (event.key.code == sf::Keyboard::Right) {
                    currentSolutionIndex = (currentSolutionIndex + 1) % totalSolutions;
                }
            }
        }

        window.clear();
        view.drawQueens(window, body, currentSolutionIndex);
        view.drawSolutionCount(window, currentSolutionIndex, totalSolutions);
        window.display();
    }
}
