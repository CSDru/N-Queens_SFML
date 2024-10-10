//
// Created by Dru on 10/1/2024.
//

#include "Model.h"
#include <cmath>

Model::Model(int size)
        : N(size), board(size, -1)
{
}

bool Model::solve(int row)
{
    if (row >= N)
    {
        solutions.push_back(board);
        return true;
    }
    bool res = false;
    for (int i = 0; i < N; ++i)
    {
        if (isSafe(row, i))
        {
            board[row] = i;
            res = solve(row + 1) || res;
            board[row] = -1;
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
    for (int r = 0; r < row; ++r)
    {
        int c = board[r];
        if (c == col || std::abs(c - col) == std::abs(r - row))
            return false;
    }
    return true;
}
