//
// Created by Dru on 10/1/2024.
//

#include "Body.h"

Body::Body(int size) : boardSize(size) {
    queens.resize(boardSize, -1); // Initialize queens positions
}

int Body::getSize() const {
    return boardSize; // Return the board size
}

void Body::solve() {
    solveNQueens(0); // Start solving from the first column
}

void Body::solveNQueens(int col) {
    if (col == boardSize) {
        solutions.push_back(queens); // Store the solution
        return;
    }

    for (int row = 0; row < boardSize; ++row) {
        if (isSafe(row, col)) {
            placeQueen(row, col);
            solveNQueens(col + 1);
            removeQueen(row, col);
        }
    }
}

bool Body::isSafe(int row, int col) {
    for (int i = 0; i < col; ++i) {
        if (queens[i] == row || // Check same row
            queens[i] - i == row - col || // Check main diagonal
            queens[i] + i == row + col) { // Check anti diagonal
            return false;
        }
    }
    return true;
}

void Body::placeQueen(int row, int col) {
    queens[col] = row; // Place queen at (row, col)
}

void Body::removeQueen(int row, int col) {
    queens[col] = -1; // Remove queen from (row, col)
}

const std::vector<std::vector<int>>& Body::getSolutions() const {
    return solutions; // Return the solutions found
}
