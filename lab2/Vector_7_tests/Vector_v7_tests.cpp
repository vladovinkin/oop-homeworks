// Vector_7_tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Vector_7/ModifyVector.h"

SCENARIO("Modifying of empty string gives an empty string")
{
	REQUIRE(ModifyVector("").empty());
}

SCENARIO("String with zeros gives zeros result")
{
	REQUIRE(ModifyVector("0 0 0 0 0") == "0.000 0.000 0.000 0.000 0.000");
}

SCENARIO("String with 1 any number gives doubled number")
{
	REQUIRE(ModifyVector("0") == "0.000");
	REQUIRE(ModifyVector("1") == "2.000");
	REQUIRE(ModifyVector("-1") == "-2.000");
}

SCENARIO("Modifying string with 2 and more numbers")
{
	REQUIRE(ModifyVector("1 -4.456 -0.0234 -2.1 3.57") == "-9.026 -6.670 -0.047 2.000 7.140");
}