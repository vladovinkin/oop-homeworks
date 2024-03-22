// SomeWeekDay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SomeWeekDay.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

std::size_t GetMonthDaysNumber(std::size_t month, std::size_t year)
{
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 2:
		return IsYearIntercalary(year) ? 29 : 28;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	default:
		assert(!"This is not possible");
		return 0;
	}
}

bool IsYearIntercalary(std::size_t year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

void CheckSameWeekDay()
{
	// читаем даты из стандартного потока
	DateYMD dateOne = ReadDate();
	DateYMD dateTwo = ReadDate();

	// сравниваем, выдаём результат
	ShowSameWeekDayResult(dateOne, dateTwo);
}

DateYMD ReadDate()
{
	std::string line;
	std::getline(std::cin, line);

	std::istringstream lineStream(line);
	DateYMD date;
	lineStream >> date.year >> date.month >> date.day;

	if (!isDateCorrect(date))
	{
		throw std::runtime_error("Error date data");
	}

	return date;
}

bool isDateCorrect(const DateYMD date)
{
	return date.year >= 1900 && date.year <= 9999
		&& date.month > 0 && date.month <= 12
		&& date.day > 0 && date.day <= GetMonthDaysNumber(date.month, date.year);
}

void ShowSameWeekDayResult(const DateYMD dateOne, const DateYMD dateTwo)
{
	if (dateOne.year != dateTwo.year)
	{
		std::cout << "ERROR\n";
		return;
	}
	auto day_count = GetDatesDeltaInDays(dateOne, dateTwo);
	std::cout << (day_count % 7 == 0 ? "Same week day" : "Different week days") << '\n';
}

std::size_t GetDatesDeltaInDays(DateYMD dateOne, DateYMD dateTwo)
{
	int delta;
	if (dateOne.month == dateTwo.month)
	{
		delta = int(dateTwo.day - dateOne.day);
	}
	else
	{
		const int monthDistance[]{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
		delta = int(monthDistance[dateOne.month] + dateOne.day - monthDistance[dateTwo.month] - dateTwo.day);
		if (IsYearIntercalary(dateOne.year) && (dateOne.month < 3 && dateTwo.month >= 3 || dateTwo.month < 3 && dateOne.month >= 3))
		{
			return std::abs(delta) + 1;
		}
	}
	return std::abs(delta);
}

int main()
{
	try
	{
		CheckSameWeekDay();
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	return 0;
}
