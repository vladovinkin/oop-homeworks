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
		std::cout << CDriver::Colorer("> ", "white");
		if (!driver.HandleCommand())
		{
			std::cout << "Unknown or inapplicable command!\n";
		}
		std::cout << '\n';
	}

    return 0;
}
