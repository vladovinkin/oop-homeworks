// Shapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "Controller.h"

int main()
{
    setlocale(LC_ALL, "rus");

    CController controller(std::cin, std::cout);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "> ";
        if (!controller.HandleCommand())
        {
            std::cout << "Unknown or inapplicable command!\n";
        }
        std::cout << '\n';
    }

    controller.PrintResult();

    return 0;
} // (+) storage -> controller
