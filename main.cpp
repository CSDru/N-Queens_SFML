#include "Controller.h"
#include <iostream>

int main()
{
    int N;
    std::cout << "Enter the number of queens (N): ";
    std::cin >> N;
    if (N <= 0)
    {
        std::cerr << "N must be a positive integer." << std::endl;
        return -1;
    }

    try
    {
        Controller controller(N);
        controller.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
