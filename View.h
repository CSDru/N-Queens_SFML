//
// Created by Dru on 10/7/2024.
//

#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include "Body.h"

class View {
public:
    void drawQueens(sf::RenderWindow& window, const Body& body, int solutionIndex);
    void drawSolutionCount(sf::RenderWindow& window, int currentSolution, int totalSolutions);
};

#endif // VIEW_H
