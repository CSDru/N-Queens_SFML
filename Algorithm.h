//
// Created by Dru on 10/1/2024.
//

#ifndef N_QUEENS_SFML_ALGORITHM_H
#define N_QUEENS_SFML_ALGORITHM_H

#include <cmath>

class Algorithm
{
private:
    int n;
    int x[];
public:
    bool Place(int row, int col);
    void solveNQueens(int row);
};


#endif //N_QUEENS_SFML_ALGORITHM_H
