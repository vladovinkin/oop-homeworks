﻿#include <iostream>
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

	GIVEN("Конструктор с тремя параметрами (день, месяц, год) создаёт определённую параметрами дату")
	{
		CDate date(7, Month::JUNE, 2250);
		CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
	}

	GIVEN("Конструктор с тремя параметрами (день, месяц, год) создаёт определённую параметрами дату")
	{
		CDate date(31, Month::DECEMBER, 9999);
		CHECK(date.GetDays() == 2932896);
	}

	GIVEN("Конструктор с тремя параметрами (день, месяц, год) создаёт определённую параметрами дату")
	{
		CDate date(24, Month::JUNE, 2577);
		CHECK(date.GetWeekDay() == WeekDay::TUESDAY);
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
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 2023);
			}
		}

		WHEN("Прибавляем к дате определённое количество дней")
		{
			CDate newDate = date + 5;
			THEN("Дата сменится на указанное количество дней")
			{
				CHECK(newDate.GetDay() == 6);
				CHECK(newDate.GetMonth() == Month::JANUARY);
				CHECK(newDate.GetYear() == 2024);
			}
		}

		WHEN("Прибавляем к определённому количеству дней дату")
		{
			CDate newDate = 59 + date;
			THEN("Дата сменится на указанное количество дней")
			{
				CHECK(newDate.GetDay() == 29);
				CHECK(newDate.GetMonth() == Month::FEBRUARY);
				CHECK(newDate.GetYear() == 2024);
			}
		}

		WHEN("Вычитаем из даты определённое количество дней")
		{
			CDate newDate = date - 3;
			THEN("Дата сменится на указанное количество дней")
			{
				CHECK(newDate.GetDay() == 29);
				CHECK(newDate.GetMonth() == Month::DECEMBER);
				CHECK(newDate.GetYear() == 2023);
			}
		}

		WHEN("Создадим дату больше данной и сравним с исходной")
		{
			CDate otherDate = date + 1;
			THEN("Другая дата не равна исходной")
			{
				CHECK(otherDate != date);
			}
			THEN("Другая дата больше исходной")
			{
				CHECK(otherDate > date);
			}
			THEN("Другая дата больше или равна исходной")
			{
				CHECK(otherDate >= date);
			}
		}

		WHEN("Создадим дату меньше данной и сравним с исходной")
		{
			CDate otherDate = date - 1;
			THEN("Другая дата не равна исходной")
			{
				CHECK(otherDate != date);
			}
			THEN("Другая дата меньше исходной")
			{
				CHECK(otherDate < date);
			}
			THEN("Другая дата меньше или равна исходной")
			{
				CHECK(otherDate <= date);
			}
		}

		WHEN("Создадим дату равную данной и сравним с исходной")
		{
			CDate otherDate = date;
			THEN("Другая дата равна исходной")
			{
				CHECK(otherDate == date);
			}
			THEN("Другая дата меньше или равна исходной")
			{
				CHECK(otherDate <= date);
			}
			THEN("Другая дата больше или равна исходной")
			{
				CHECK(otherDate >= date);
			}
		}

		WHEN("Прибавляем к дате определённое количество дней при помощи оператора +=")
		{
			date += 366;
			THEN("Дата сменится на указанное количество дней")
			{
				CHECK(date.GetDay() == 1);
				CHECK(date.GetMonth() == Month::JANUARY);
				CHECK(date.GetYear() == 2025);

			}
		}

		WHEN("Вычитаем из даты определённое количество дней при помощи оператора -=")
		{
			date -= 366;
			THEN("Дата сменится на указанное количество дней")
			{
				CHECK(date.GetDay() == 31);
				CHECK(date.GetMonth() == Month::DECEMBER);
				CHECK(date.GetYear() == 2022);
			}
		}

		WHEN("Выводим дату в поток вывода <<")
		{
			std::ostringstream output;
			output << date;
			THEN("Дата окажется в потоке вывода")
			{
				CHECK(output.str() == "01.01.2024");
			}
		}

		WHEN("Вводим дату через поток >>")
		{
			std::istringstream input("12.04.2024");
			input >> date;
			THEN("В объекте окажется указанная дата")
			{
				CHECK(date.GetDay() == 12);
				CHECK(date.GetMonth() == Month::APRIL);
				CHECK(date.GetYear() == 2024);
				CHECK(date.GetWeekDay() == WeekDay::FRIDAY);
			}
		}
	}
}

TEST_CASE("Разность двух дат - даты разные")
{
	setlocale(LC_ALL, "rus");

	CDate date1(29, Month::MAY, 1982);
	CDate date2(23, Month::JUNE, 2024);
	CHECK(date1 - date2 == -15366);
	CHECK(date2 - date1 == 15366);
}

TEST_CASE("Разность двух дат - даты одинаковые")
{
	setlocale(LC_ALL, "rus");

	CDate date1(23, Month::JUNE, 2024);
	CDate date2(23, Month::JUNE, 2024);
	CHECK(date1 - date2 == 0);
}

TEST_CASE("Сложение даты и отрицательного количества дней")
{
	setlocale(LC_ALL, "rus");

	CDate date(24, Month::JUNE, 2024);
	int days = -30;
	CHECK((date + days).GetDay() == 25);
	CHECK((date + days).GetMonth() == Month::MAY);
	CHECK((date + days).GetYear() == 2024);
}

TEST_CASE("Сложение отрицательного количества дней и даты")
{
	setlocale(LC_ALL, "rus");

	CDate date(24, Month::JUNE, 2024);
	int days = -5;
	CHECK((days + date).GetDay() == 19);
	CHECK((days + date).GetMonth() == Month::JUNE);
	CHECK((days + date).GetYear() == 2024);
}

TEST_CASE("Вычитание из даты отрицательного количества дней")
{
	setlocale(LC_ALL, "rus");

	CDate date(24, Month::JUNE, 2024);
	int days = -30;
	CHECK((date - days).GetDay() == 24);
	CHECK((date - days).GetMonth() == Month::JULY);
	CHECK((date - days).GetYear() == 2024);
}
