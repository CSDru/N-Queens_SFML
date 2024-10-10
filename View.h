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

    sf::Color white, black, queenColor, labelColor, buttonColor, buttonHoverColor, outlineColor;
    sf::RectangleShape yesButton, noButton;

    // Drawing functions
    void drawBoard();
    void drawQueens(const std::vector<int>& board);
    void drawLabel(size_t current, size_t total);
    void drawDigit(int digit, float x, float y, float size);
    void drawSlash(float x, float y, float size);
    void drawDigits(const std::string& digits, float x, float y, float digitSize);
    void drawConfirmationDialog(int selectedButton); // Add this line
};

#endif // VIEW_H
