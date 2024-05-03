// Task.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "car.h"
#include "driver.h"

int main()
{
    setlocale(LC_ALL, "rus");

    CCar car;
    CDriver driver(car, std::cin, std::cout);
    
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << CDriver::Colorer("> ", White);
		if (!driver.HandleCommand())
		{
			std::cout << CDriver::Colorer("Unknown or inapplicable command!", Red) + '\n';
		}
		std::cout << '\n';
	}

    return 0;
}
