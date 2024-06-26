#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyStack/CMyStack.h"

TEST_CASE("Create empty stack")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();

	REQUIRE(stack.Empty() == true);
}
