// Shapes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "CController.h"

int main()
{
    setlocale(LC_ALL, "rus");

    CController controller(std::cin, std::cout);

    while (!std::cin.eof() && !std::cin.fail())
    {
        std::cout << "> ";
        int handlerResponse = controller.HandleCommand();
        if (handlerResponse != ResponseEnd)
        {
            switch (handlerResponse)
            {
            case ResponseUnknownCommand:
                std::cout << "Unknown command\n";
                break;
            case ResponseInvalidArguments:
                std::cout << "Invalid arguments\n";
                break;
            }
        }
        else
        {
            break;
        }
        std::cout << '\n';
    }

    controller.PrintResult();

    return 0;
}
