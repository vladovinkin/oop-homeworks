#include <iostream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../CMyStack/CMyStack.h"

TEST_CASE("Создал пустой стек целых чисел")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();

	CHECK(stack.Empty() == true);
}

TEST_CASE("Добавил в стек целых чисел два целых числа")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Push(531);
	stack.Push(-198);

	CHECK(stack.Empty() == false);
	CHECK(stack.Top() == -198);
	CHECK(stack.Size() == 2);
}

TEST_CASE("Добавил в стек целых чисел два целых числа и одно удалил")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Push(12);
	stack.Push(1982);
	stack.Pop();

	CHECK(stack.Empty() == false);
	CHECK(stack.Top() == 12);
	CHECK(stack.Size() == 1);
}

TEST_CASE("Добавил в стек целых чисел три целых числа и очистил стек")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Push(-5);
	stack.Push(32);
	stack.Push(0);
	stack.Clear();

	CHECK(stack.Empty() == true);
	CHECK(stack.Size() == 0);
}

TEST_CASE("Создал стек и очистил стек")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Clear();

	CHECK(stack.Empty() == true);
	CHECK(stack.Size() == 0);
}

TEST_CASE("В стек целых чисел добавил одно целое число и попытался удалить три раза")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Push(11);
	stack.Pop();
	stack.Pop();
	stack.Pop();

	CHECK(stack.Empty() == true);
	CHECK(stack.Size() == 0);
}

TEST_CASE("Создал стек, добавил три целых числа и на основе его создал ещё стек")
{
	setlocale(LC_ALL, "rus");

	CMyStack<int> stack = CMyStack<int>();
	stack.Push(11);
	stack.Push(22);
	stack.Push(33);

	CMyStack<int> newStack = CMyStack<int>(stack);

	CHECK(newStack.Empty() == false);
	CHECK(newStack.Size() == 3);
	CHECK(newStack.Top() == 33);

	newStack.Pop();

	CHECK(newStack.Size() == 2);
	CHECK(newStack.Top() == 22);

	newStack.Pop();

	CHECK(newStack.Size() == 1);
	CHECK(newStack.Top() == 11);

	newStack.Pop();

	CHECK(newStack.Empty() == true);
	CHECK(newStack.Size() == 0);
}

TEST_CASE("Создал пустой стек строк")
{
	setlocale(LC_ALL, "rus");

	CMyStack<std::string> stack = CMyStack<std::string>();

	CHECK(stack.Empty() == true);
}

TEST_CASE("Добавил в стек строк три элемента")
{
	setlocale(LC_ALL, "rus");

	CMyStack<std::string> stack = CMyStack<std::string>();
	stack.Push("One");
	stack.Push("Two");
	stack.Push("Fifteen");

	CHECK(stack.Empty() == false);
	CHECK(stack.Top() == "Fifteen");
	CHECK(stack.Size() == 3);
}
