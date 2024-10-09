//
// Created by Dru on 10/1/2024.
//

#include "Model.h"
#include <cmath>

Model::Model(int size)
        : N(size), board(size, -1)
{
}

bool Model::solve(int col)
{
    if (col >= N)
    {
        solutions.push_back(board);
        return true;
    }
    bool res = false;
    for (int i = 0; i < N; ++i)
    {
        if (isSafe(i, col))
        {
            board[col] = i;
            res = solve(col + 1) || res;
            board[col] = -1;
        }
    }
    return res;
}

const std::vector<std::vector<int>>& Model::getSolutions() const
{
    return solutions;
}

const std::vector<int>& Model::getBoard() const
{
    return board;
}

bool Model::isSafe(int row, int col)
{
    for (int c = 0; c < col; ++c)
    {
        int r = board[c];
        if (r == row || std::abs(r - row) == std::abs(c - col))
            return false;
    }
    return true;
}
