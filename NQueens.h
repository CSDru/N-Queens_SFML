//
// Created by Dru on 10/7/2024.
//

#ifndef NQUEENS_H
#define NQUEENS_H

#include <vector>
#include <string>

class NQueens {
public:
    explicit NQueens(int n);
    std::vector<std::vector<std::string>> solveNQueens();
private:
    void backtrack(int row);
    bool isSafe(int row, int col);

    int n;
    std::vector<std::vector<std::string>> solutions;
    std::vector<std::string> board;
};

#endif // NQUEENS_H
