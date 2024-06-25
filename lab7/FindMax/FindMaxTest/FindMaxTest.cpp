#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../FindMax/FindMaxT.h"

SCENARIO("Проверка массивов int")
{
	setlocale(LC_ALL, "rus");

	GIVEN("Функция с пустым массивом int должен вернуть false")
	{
		std::vector<int> ints = {};
		int maxInt;
		CHECK(!FindMax(ints, maxInt));
	}

	GIVEN("Функция с непустым массивом int должен вернуть true и максимальный вариант")
	{
		std::vector<int> ints = { 5, 4, 3, 6, 0 };
		int maxInt;
		CHECK(FindMax(ints, maxInt));
		CHECK(maxInt == 6);
	}
}

SCENARIO("Проверка массивов float")
{
	setlocale(LC_ALL, "rus");

	GIVEN("Функция с пустым массивом float должен вернуть false")
	{
		std::vector<float> floats = {};
		float maxFloat;
		CHECK(!FindMax(floats, maxFloat));
	}

	GIVEN("Функция с непустым массивом float должен вернуть true и максимальный вариант")
	{
		std::vector<float> floats = { 5.3f, 0.4f, 7.3f, 6.1f, 0.3f };
		float maxFloat;
		CHECK(FindMax(floats, maxFloat));
		CHECK(maxFloat == 7.3f);
	}
}

SCENARIO("Проверка массивов string")
{
	setlocale(LC_ALL, "rus");

	GIVEN("Функция с пустым массивом string должен вернуть false")
	{
		std::vector<std::string> strings = {};
		std::string maxString;
		CHECK(!FindMax(strings, maxString));
	}

	GIVEN("Функция с непустым массивом string должен вернуть true и максимальный вариант")
	{
		std::vector<std::string> strings = { "this", "is", "a", "super", "puper" };
		std::string maxString;
		CHECK(FindMax(strings, maxString));
		CHECK(maxString == "this");
	}
}

SCENARIO("Проверка массивов указателей на строки")
{
	setlocale(LC_ALL, "rus");

	GIVEN("Функция с пустым массивом указателей на строки должен вернуть false")
	{
		std::vector<std::string> strings = {};
		std::string maxString;
		CHECK(!FindMax(strings, maxString));
	}

	GIVEN("Функция с непустым массивом указателей на строки должен вернуть true и максимальный вариант")
	{
		std::vector<const char*> strings = { "how", "much", "is", "the", "fish" };
		const char* maxString;
		CHECK(FindMax(strings, maxString));
		CHECK(strcmp(maxString, "the") == 0);
	}
}

SCENARIO("Проверка массивов объектов классов")
{
	setlocale(LC_ALL, "rus");

	class Some
	{
	public:
		Some() = default;
		Some(const Some&) { throw std::exception("Some error!"); }

		Some& operator>(Some&) { return *this; };

	private:
		int m_duck;
	};
}
