//
// Created by Dru on 10/7/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Model.h"
#include "View.h"

class Controller
{
public:
    Controller(int size);

    void run();

private:
    Model model;
    View view;
};

#endif // CONTROLLER_H
