// SomeWeekDay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SomeWeekDay.h"
#include <iostream>
#include <optional>

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: SomeWeekDay.exe <date1_string> <date2_string>\n";
		return std::nullopt;
	}
	Args args;
	args.dateOne = argv[1];
	args.dateTwo = argv[2];
	return args;
}

int GetMonthDaysNumber(int month, int year)
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
	}
	return 30;
}

bool IsYearIntercalary(int year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

int main(int argc, char* argv[])
{
	DateYMD dateOne, dateTwo;

	// Проверка правильности аргументов командной строки
	auto args = ParseArgs(argc, argv);

	if (!ReadDate(dateOne))
	{
		std::cout << "Incorrect first date format '" << argv[1] << "'\n";
		std::cout << "Please, use next date format: \"YYYY MM DD\""
				  << "'\n";
		return 1;
	}

	if (!ReadDate(dateTwo))
	{
		std::cout << "Incorrect second date format '" << argv[1] << "'\n";
		std::cout << "Please, use next date format: \"YYYY MM DD\""
				  << "'\n";
		return 1;
	}

	if (dateOne.year != dateTwo.year)
	{
		std::cout << "ERROR\n";
		return 1;
	}
	
	return 0;
}