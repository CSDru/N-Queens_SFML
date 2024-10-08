//
// Created by Dru on 10/7/2024.
//

#include "NQueens.h"
#include <string>

NQueens::NQueens(int n) : n(n), board(n, std::string(n, '.')) {}

std::vector<std::vector<std::string>> NQueens::solveNQueens() {
    backtrack(0);
    return solutions;
}

void NQueens::backtrack(int row) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col)) {
            board[row][col] = 'Q'; // Place queen
            backtrack(row + 1);     // Recur to place next queen
            board[row][col] = '.';  // Remove queen (backtrack)
        }
    }
}

bool NQueens::isSafe(int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q') return false; // Check column

        if (col - (row - i) >= 0 && board[i][col - (row - i)] == 'Q') return false; // Check left diagonal
        if (col + (row - i) < n && board[i][col + (row - i)] == 'Q') return false; // Check right diagonal
    }
    return true;
}
