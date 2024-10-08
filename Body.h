//
// Created by Dru on 10/1/2024.
//

#ifndef BODY_H
#define BODY_H

#include <vector>

class Body {
public:
    Body(int size); // Constructor that takes board size
    void solve(); // Method to find solutions
    const std::vector<std::vector<int>>& getSolutions() const; // Method to get solutions
    int getSize() const; // Method to get board size

private:
    int boardSize; // Change from 'size' to 'boardSize' for clarity
    std::vector<int> queens; // Vector to hold positions of queens
    std::vector<std::vector<int>> solutions; // Vector to hold solutions

    bool isSafe(int row, int col);
    void placeQueen(int row, int col);
    void removeQueen(int row, int col);
    void solveNQueens(int col);
};

#endif // BODY_H
