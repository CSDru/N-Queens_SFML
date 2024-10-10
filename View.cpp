//
// Created by Dru on 10/7/2024.
//

#include "View.h"
#include <iostream>

// Constructor
View::View(int size, int windowSize)
        : N(size), window(sf::VideoMode(windowSize, windowSize + 100), "N-Queens Visualization"), cellSize(static_cast<float>(windowSize) / N)
{
    window.setFramerateLimit(60);
    white = sf::Color::White;
    black = sf::Color(100, 100, 100);
    queenColor = sf::Color::Red;
    labelColor = sf::Color::Black;
    buttonColor = sf::Color(200, 200, 200);
    buttonHoverColor = sf::Color(150, 150, 150);
    outlineColor = sf::Color::Blue;

    // Initialize Yes Button
    yesButton.setSize(sf::Vector2f(100.0f, 50.0f));
    yesButton.setFillColor(buttonColor);
    yesButton.setPosition((windowSize / 2) - 140.0f, windowSize / 2 + 10.0f);
    yesButton.setOutlineThickness(2.0f);
    yesButton.setOutlineColor(sf::Color::Transparent);

    // Initialize No Button
    noButton.setSize(sf::Vector2f(100.0f, 50.0f));
    noButton.setFillColor(buttonColor);
    noButton.setPosition((windowSize / 2) + 40.0f, windowSize / 2 + 10.0f);
    noButton.setOutlineThickness(2.0f);
    noButton.setOutlineColor(sf::Color::Transparent);
}

// Draw method now includes solution label and optional confirmation dialog
void View::draw(const std::vector<int>& board, size_t current, size_t total, bool showDialog, int selectedButton)
{
    window.clear(sf::Color::White); // Clear with white background
    drawBoard();
    drawQueens(board);
    drawLabel(current, total);

    if (showDialog)
    {
        drawConfirmationDialog(selectedButton);
    }

    window.display();
}

bool View::isOpen() const
{
    return window.isOpen();
}

std::vector<sf::Event> View::handleEvents()
{
    std::vector<sf::Event> events;
    sf::Event event;
    while (window.pollEvent(event))
    {
        events.push_back(event);
    }
    return events;
}

void View::drawBoard()
{
    sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            rect.setPosition(j * cellSize, i * cellSize);
            if ((i + j) % 2 == 0)
                rect.setFillColor(white);
            else
                rect.setFillColor(black);
            window.draw(rect);
        }
    }
}

void View::drawQueens(const std::vector<int>& board)
{
    sf::CircleShape queen(cellSize / 2 - 10, 100);  // Simple circle with radius based on cellSize
    queen.setFillColor(queenColor);                 // Set the fill color to the queenColor

    for (int col = 0; col < static_cast<int>(board.size()); ++col)
    {
        int row = board[col];
        if (row != -1)
        {
            // Position the queen circle in the center of each square
            queen.setPosition(col * cellSize + (cellSize - queen.getRadius() * 2) / 2, row * cellSize + (cellSize - queen.getRadius() * 2) / 2);
            window.draw(queen);  // Draw the queen circle
        }
    }
}

// Helper function to draw the solution label
void View::drawLabel(size_t current, size_t total)
{
    // Position the label below the chessboard
    float labelX = 10.0f;
    float labelY = N * cellSize + 30.0f; // Raised by 30 pixels

    float digitSize = 30.0f; // Size of each digit
    float spaceBetween = 10.0f; // Space between digits, can be adjusted as needed

    // Calculate the width for the current number
    std::string currentStr = std::to_string(current + 1);
    float currentWidth = currentStr.length() * (digitSize);

    // Calculate the width for the total number
    std::string totalStr = std::to_string(total);
    float totalWidth = totalStr.length() * (digitSize);

    // Draw current number
    drawDigits(currentStr, labelX, labelY, digitSize);

    // Draw slash '/'
    drawSlash(labelX + currentWidth, labelY, digitSize); // Adjust position to account for space

    // Draw total number
    drawDigits(totalStr, labelX * 2 + currentWidth + spaceBetween * 2, labelY, digitSize);
}

// Helper function to draw multiple digits
void View::drawDigits(const std::string& digits, float x, float y, float digitSize)
{
    for (char digit : digits)
    {
        // Assuming drawDigit is a method that takes the digit character and draws it
        drawDigit(digit - '0', x, y, digitSize); // Convert char to int
        x += digitSize; // Move x position for the next digit
    }
}



// Helper function to draw individual digits using lines
void View::drawDigit(int number, float x, float y, float size)
{
    // Each digit is represented by 7 segments
    bool segments[10][7] =
            {
                    {true, true, true, false, true, true, true}, // 0
                    {false, false, true, false, false, true, false}, // 1
                    {true, false, true, true, true, false, true}, // 2
                    {true, false, true, true, false, true, true}, // 3
                    {false, true, true, true, false, true, false}, // 4
                    {true, true, false, true, false, true, true}, // 5
                    {true, true, false, true, true, true, true}, // 6
                    {true, false, true, false, false, true, false}, // 7
                    {true, true, true, true, true, true, true}, // 8
                    {true, true, true, true, false, true, true} // 9
            };

    // Convert the number to a string to handle multi-digit numbers
    std::string numberStr = std::to_string(number);
    float thickness = size / 10.0f;
    float length = size * 0.6f;

    // Draw each digit in the number
    for (size_t i = 0; i < numberStr.length(); ++i)
    {
        int digit = numberStr[i] - '0'; // Convert character to int
        float offsetX = i * (length + thickness * 2); // Calculate offset for each digit

        // Add segments based on the digit
        std::vector<sf::RectangleShape> segmentShapes;

        if (segments[digit][0])
        {
            sf::RectangleShape seg(sf::Vector2f(length, thickness));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX, y);
            segmentShapes.push_back(seg);
        }
        if (segments[digit][1])
        {
            sf::RectangleShape seg(sf::Vector2f(thickness, length));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX, y + thickness);
            segmentShapes.push_back(seg);
        }
        if (segments[digit][2])
        {
            sf::RectangleShape seg(sf::Vector2f(thickness, length));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX + length - thickness, y + thickness);
            segmentShapes.push_back(seg);
        }
        if (segments[digit][3])
        {
            sf::RectangleShape seg(sf::Vector2f(length, thickness));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX, y + length + thickness);
            segmentShapes.push_back(seg);
        }
        if (segments[digit][4])
        {
            sf::RectangleShape seg(sf::Vector2f(thickness, length));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX, y + 2 * length + 2 * thickness - 18.0f);
            segmentShapes.push_back(seg);
        }
        if (segments[digit][5])
        {
            sf::RectangleShape seg(sf::Vector2f(thickness, length));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX + length - thickness, y + 2 * length + 2 * thickness - 18.0f);
            segmentShapes.push_back(seg);
        }
        if (segments[digit][6])
        {
            sf::RectangleShape seg(sf::Vector2f(length, thickness));
            seg.setFillColor(labelColor);
            seg.setPosition(x + offsetX, y + 3 * length + 3 * thickness - 22.0f);
            segmentShapes.push_back(seg);
        }

        // Draw all active segments for this digit
        for (const auto& seg : segmentShapes)
        {
            window.draw(seg);
        }
    }
}



// Helper function to draw the slash '/' with correct orientation and size
void View::drawSlash(float x, float y, float size)
{
    sf::RectangleShape slash(sf::Vector2f(size * 1.6f, 3.0f)); // Increased size and thickness
    slash.setFillColor(labelColor);
    slash.setPosition(x - size * 0.1f, y + size * 1.4f); // Adjusted position
    slash.setRotation(-60.0f); // Flipped the slash to '/'
    window.draw(slash);
}

// Helper function to draw the confirmation dialog
void View::drawConfirmationDialog(int selectedButton)
{
    // Draw semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
    window.draw(overlay);

    // Draw dialog box
    float dialogWidth = 400.0f;
    float dialogHeight = 200.0f;
    sf::RectangleShape dialogBox(sf::Vector2f(dialogWidth, dialogHeight));
    dialogBox.setFillColor(sf::Color::White);
    dialogBox.setPosition((window.getSize().x - dialogWidth) / 2, (window.getSize().y - dialogHeight) / 2);
    dialogBox.setOutlineThickness(2.0f);
    dialogBox.setOutlineColor(sf::Color::Black);
    window.draw(dialogBox);

    // Draw confirmation text using digits (since no fonts)
    // Here, we use simple shapes to represent "Exit?"
    // Alternatively, we can omit the text or use graphical symbols

    // For simplicity, we'll represent "Exit?" as two triangles (like arrows) and a question mark
    // Or we can skip the text and just have the buttons

    // Draw buttons: Yes and No
    window.draw(yesButton);
    window.draw(noButton);

    // Draw button labels as digits or simple shapes (since no fonts)
    // For "Yes" and "No", we'll draw simple labels

    // Simple representation:
    // "Y" as a vertical line with a horizontal line at the middle
    // "N" as two diagonal lines and a vertical line

    // Position for "Yes" button label
    float yesLabelX = yesButton.getPosition().x + 40.0f;
    float yesLabelY = yesButton.getPosition().y + 15.0f;
    float labelSize = 20.0f;

    // Draw "Y"
    // Vertical line
    sf::RectangleShape yVertical(sf::Vector2f(3.0f, labelSize - 4.0f));
    yVertical.setFillColor(labelColor);
    yVertical.setPosition(yesLabelX + 5.0f, yesLabelY + 7.0f);
    window.draw(yVertical);

    // Diagonal lines
    sf::RectangleShape yDiagonal1(sf::Vector2f(3.0f, labelSize / 2));
    yDiagonal1.setFillColor(labelColor);
    yDiagonal1.setPosition(yesLabelX + 13.0f, yesLabelY + 0.0f);
    yDiagonal1.setRotation(45.0f);
    window.draw(yDiagonal1);

    sf::RectangleShape yDiagonal2(sf::Vector2f(3.0f, labelSize / 2));
    yDiagonal2.setFillColor(labelColor);
    yDiagonal2.setPosition(yesLabelX - 2.0f, yesLabelY + 2.0f);
    yDiagonal2.setRotation(-45.0f);
    window.draw(yDiagonal2);

    // Position for "No" button label
    float noLabelX = noButton.getPosition().x + 40.0f;
    float noLabelY = noButton.getPosition().y + 15.0f;

    // Draw "N"
    // Left vertical line
    sf::RectangleShape nVerticalLeft(sf::Vector2f(3.0f, labelSize));
    nVerticalLeft.setFillColor(labelColor);
    nVerticalLeft.setPosition(noLabelX, noLabelY);
    window.draw(nVerticalLeft);

    // Diagonal line
    sf::RectangleShape nDiagonal(sf::Vector2f(3.0f, labelSize));
    nDiagonal.setFillColor(labelColor);
    nDiagonal.setPosition(noLabelX + 1.0f, noLabelY + 3.0f);
    nDiagonal.setRotation(-30.0f);
    window.draw(nDiagonal);

    // Right vertical line
    sf::RectangleShape nVerticalRight(sf::Vector2f(3.0f, labelSize));
    nVerticalRight.setFillColor(labelColor);
    nVerticalRight.setPosition(noLabelX + 10.0f, noLabelY);
    window.draw(nVerticalRight);

    // Highlight the selected button
    if (selectedButton == 0)
    {
        yesButton.setOutlineColor(outlineColor);
        noButton.setOutlineColor(sf::Color::Transparent);
    }
    else if (selectedButton == 1)
    {
        noButton.setOutlineColor(outlineColor);
        yesButton.setOutlineColor(sf::Color::Transparent);
    }
    else
    {
        yesButton.setOutlineColor(sf::Color::Transparent);
        noButton.setOutlineColor(sf::Color::Transparent);
    }
}

// Helper function to check if mouse is over a button
bool View::isMouseOverButton(const sf::Vector2f& mousePos, const sf::RectangleShape& button) const
{
    return button.getGlobalBounds().contains(mousePos);
}
