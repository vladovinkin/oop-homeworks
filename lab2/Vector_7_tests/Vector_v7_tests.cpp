// Vector_7_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Vector_7/ModifyVector.h"

SCENARIO("Modifying of empty string gives an empty string")
{
	std::vector<double> numbers = {};
	ModifyVector(numbers);
	REQUIRE(numbers.empty());
}

SCENARIO("String with zeros gives zeros result")
{
	std::vector<double> numbers = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	std::vector<double> numbersResult = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);
}

SCENARIO("String with 1 any number gives doubled number")
{
	std::vector<double> numbers = { 0.0 };
	std::vector<double> numbersResult = { 0.0 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);

	numbers = { 1.0 };
	numbersResult = { 2.0 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);

	numbers = { -1.0 };
	numbersResult = { -2.0 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);
}

SCENARIO("Modifying string with 2 and more numbers")
{
	std::vector<double> numbers = { -5.436, -6.9876 };
	std::vector<double> numbersResult = { -10.872, -6.9876 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);

	numbers = { 4.456, 1.534 };
	numbersResult = { -4.456, 8.912 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);

	numbers = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	numbersResult = { -13.0, -11.0, 2.0, 6.0, 10.0 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);

	numbers = { 1.0, -4.456, -0.0234, -2.1, 3.57 };
	numbersResult = { -9.026, -6.67, -0.0468, 2.0, 7.14 };
	ModifyVector(numbers);
	REQUIRE(numbers == numbersResult);
}