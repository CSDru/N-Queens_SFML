//
// Created by Dru on 10/1/2024.
//

#ifndef MODEL_H
#define MODEL_H

#include <vector>

class Model
{
public:
    Model(int size);

    bool solve(int col = 0);

    const std::vector<std::vector<int>>& getSolutions() const;

    const std::vector<int>& getBoard() const;

private:
    int N;
    std::vector<int> board;
    std::vector<std::vector<int>> solutions;

    bool isSafe(int row, int col);
};

#endif // MODEL_H
