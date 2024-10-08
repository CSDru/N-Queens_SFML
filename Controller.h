//
// Created by Dru on 10/7/2024.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Body.h" // Ensure you include the Body header
#include "View.h" // Ensure you include the View header

class Controller {
public:
    Controller(); // Constructor declaration
    void run(); // Method to start the application

private:
    Body body; // Instance of Body class to handle N-Queens logic
    View view; // Instance of View class to handle display
};

#endif // CONTROLLER_H
