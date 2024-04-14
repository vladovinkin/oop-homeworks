// Vector_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ModifyVector.h"

int main()
{
	try
	{
		// (+) посмотреть примеры в которых разобраны варианты и прочитать вектор по другому
		std::vector<double> numbers(std::istream_iterator<double>(std::cin), (std::istream_iterator<double>()));
		ModifyVector(numbers);
		PrintVector(numbers);
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	return 0;
}
