#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyStack/CMyStack.h"

TEST_CASE("Create empty stack")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();

	CHECK(stack.Empty() == true);
}

TEST_CASE("Push two elements, size mus be = 2, top must be second element")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Push(531);
	stack.Push(-198);

	CHECK(stack.Empty() == false);
	CHECK(stack.Top() == -198);
	CHECK(stack.Size() == 2);
}
