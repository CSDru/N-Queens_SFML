//
// Created by Dru on 10/1/2024.
//

#include "Algorithm.h"

bool Algorithm::Place(int row, int col)
{
    for(int i = 1; i < row; ++i)
    {
        if(x[i] == col || abs(x[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

void Algorithm::solveNQueens(int row)
{
    for(int i = 1; i < n; ++i)
    {
        if(Place(row, i))
        {
            x[row] = i;
            if(row == n)
                write(x[1:n]);
            else
                solveNQueens(row++);
        }
    }
}
