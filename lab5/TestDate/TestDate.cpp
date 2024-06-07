#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Calendar/CDate.h"

SCENARIO("Проверка конструкторов")
{
	setlocale(LC_ALL, "rus");

	GIVEN("Конструктор без параметров должен создать дату 1 января 1970 года (четверг)")
	{
		CDate date;
		CHECK(date.GetWeekDay() == WeekDay::THURSDAY);
		CHECK(date.GetDays() == 0);
		CHECK(date.GetDay() == 1);
		CHECK(date.GetMonth() == Month::JANUARY);
		CHECK(date.GetYear() == 1970);
	}

	GIVEN("Конструктор с одним параметром создаёт дату, которая находится позже даты 1 января 1970 года на величину параметра")
	{
		CDate date(500);
		CHECK(date.GetWeekDay() == WeekDay::SUNDAY);
		CHECK(date.GetDays() == 500);
		CHECK(date.GetDay() == 16);
		CHECK(date.GetMonth() == Month::MAY);
		CHECK(date.GetYear() == 1971);
	}

	GIVEN("Конструктор с тремя параметрами (день, месяц, год) создаёт определённую параметрами дату")
	{
		CDate date(7, Month::JUNE, 2024);
		CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
		CHECK(date.GetDays() == 19881);
		CHECK(date.GetDay() == 7);
		CHECK(date.GetMonth() == Month::JUNE);
		CHECK(date.GetYear() == 2024);
	}
}

SCENARIO("Проверка перегрузки операторов")
{
	setlocale(LC_ALL, "rus");

	GIVEN("Задана любая дата")
	{
		CDate date(1, Month::JANUARY, 2024);

		WHEN("Выполнено префиксное приращение")
		{
			++date;
			THEN("Дата сменится на следующий день")
			{
				CHECK(date.GetDay() == 2);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 2024);

			}
		}

		WHEN("Выполнено префиксное уменьшение")
		{
			--date;
			THEN("Дата сменится на предыдущий день")
			{
				CHECK(date.GetDay() ==31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Выполнено постфиксное приращение")
		{
			date++;
			THEN("Дата сменится на следующий день")
			{
				CHECK(date.GetDay() == 2);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 2024);
			}
		}

		WHEN("Выполнено постфиксное уменьшение")
		{
			date--;
			THEN("Дата сменится на предыдущий день")
			{
				CHECK(date.GetDay() ==31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 2023);
			}
		}
	}
}
