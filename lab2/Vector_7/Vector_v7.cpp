// Vector_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ModifyVector.h"

int main()
{
	try
	{
		std::string line;
		std::getline(std::cin, line);
		// посмотреть примеры в которых разобраны варианты и прочитать вектор по другому
		std::cout << ModifyVector(line) << '\n';
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	return 0;
}
