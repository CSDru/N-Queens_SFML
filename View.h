//
// Created by Dru on 10/7/2024.
//

//
// Created by Dru on 10/7/2024.
//

#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>
#include <vector>

class View
{
public:
    View(int size, int windowSize = 600);

    // Updated draw method to include solution label and optional confirmation dialog
    void draw(const std::vector<int>& board, size_t current, size_t total, bool showDialog = false, int selectedButton = 0);

    bool isOpen() const;

    std::vector<sf::Event> handleEvents();

    // Methods to check if mouse is over a button
    bool isMouseOverButton(const sf::Vector2f& mousePos, const sf::RectangleShape& button) const;
    sf::RenderWindow& getWindow() { return window; }
    sf::RectangleShape& getYesButton() { return yesButton; }
    sf::RectangleShape& getNoButton() { return noButton; }

private:
    int N;
    float cellSize;
    sf::RenderWindow window;
    sf::Color white;
    sf::Color black;
    sf::Color queenColor;
    sf::Color labelColor;
    sf::Color buttonColor;
    sf::Color buttonHoverColor;
    sf::Color outlineColor;

    // Buttons for confirmation dialog
    sf::RectangleShape yesButton;
    sf::RectangleShape noButton;

    // Button labels (using simple lines and shapes)
    void drawBoard();
    void drawQueens(const std::vector<int>& board);
    void drawLabel(size_t current, size_t total);
    void drawDigit(int digit, float x, float y, float size);
    void drawSlash(float x, float y, float size);
    void drawConfirmationDialog(int selectedButton);
};

#endif // VIEW_H
