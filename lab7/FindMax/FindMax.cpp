﻿#include <iostream>
#include <string>
#include <vector>

template < typename T >
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.size())
	{
		maxValue = arr[0];
		for (auto i = 1; i < arr.size(); i++)
		{
			maxValue = maxValue > arr[i] ? maxValue : arr[i];
		}
		return true;
	}
	return false;
}

int main()
{
	std::vector<int> numbers = { 5, 4, 3, 6, 0 };
	int max1;
	if (FindMax(numbers, max1))
	{
		std::cout << "max int: " << max1 << "\n";
	}

	std::vector<float> numbersF = { 5.3f, 0.4f, 7.3f, 6.1f, 0.3f };
	float max2;
	if (FindMax(numbersF, max2))
	{
		std::cout << "max float: " << max2 << "\n";
	}

	std::vector<std::string> itemsS = { "this", "is", "a", "super", "puper" };
	std::string max3;
	if (FindMax(itemsS, max3))
	{
		std::cout << "max string: " << max3 << "\n";
	}

	std::vector<std::string> itemsS = { };
	std::string max4;
	if (FindMax(itemsS, max3))
	{
		std::cout << "max string: " << max4 << "\n";
	}

	return 0;
}
