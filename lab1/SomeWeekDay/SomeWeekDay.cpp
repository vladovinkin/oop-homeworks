// SomeWeekDay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <iostream>
#include <optional>
#include <sstream>

struct DateYMD
{
	int year;
	int month;
	int day;
};

struct Args
{
	std::string fileName;
};

constexpr int DaysBeforeJanuary = 0;
constexpr int DaysBeforeFebruary = DaysBeforeJanuary + 31;
constexpr int DaysBeforeMarch = DaysBeforeFebruary + 28;
constexpr int DaysBeforeApril = DaysBeforeMarch + 31;
constexpr int DaysBeforeMay = DaysBeforeApril + 30;
constexpr int DaysBeforeJune = DaysBeforeMay + 31;
constexpr int DaysBeforeJuly = DaysBeforeJune + 30;
constexpr int DaysBeforeAugust = DaysBeforeJuly + 31;
constexpr int DaysBeforeSeptember = DaysBeforeAugust + 31;
constexpr int DaysBeforeOctober = DaysBeforeSeptember + 30;
constexpr int DaysBeforeNovember = DaysBeforeOctober + 31;
constexpr int DaysBeforeDecember = DaysBeforeNovember + 30;

constexpr int DaysToMonth[] = {
	DaysBeforeJanuary,
	DaysBeforeFebruary,
	DaysBeforeMarch,
	DaysBeforeApril,
	DaysBeforeMay,
	DaysBeforeJune,
	DaysBeforeJuly,
	DaysBeforeAugust,
	DaysBeforeSeptember,
	DaysBeforeOctober,
	DaysBeforeNovember,
	DaysBeforeDecember
};

bool IsYearLeap(std::size_t year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

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
		return IsYearLeap(year) ? 29 : 28;
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

bool IsDateCorrect(const DateYMD& date)
{
	return date.year >= 1900 && date.year <= 9999
		&& date.month > 0 && date.month <= 12
		&& date.day > 0 && date.day <= GetMonthDaysNumber(date.month, date.year);
}

DateYMD ReadDate()
{
	std::string line;
	std::getline(std::cin, line);

	std::istringstream lineStream(line);
	DateYMD date;
	lineStream >> date.year >> date.month >> date.day;

	if (!IsDateCorrect(date))
	{
		throw std::runtime_error("Error date data");
	}

	return date;
}

int GetDaysToDate(const DateYMD& date)
{
	// Если год високосный и месяц март и выше, добавить один день
	if (IsYearLeap(date.year) && date.month >= 2)
	{
		return DaysToMonth[date.month - 1] + date.day + 1;
	}
	return DaysToMonth[date.month - 1] + date.day;
}

std::size_t GetDatesDeltaInDays(const DateYMD& dateOne, const DateYMD& dateTwo)
{
	return std::abs(GetDaysToDate(dateOne) - GetDaysToDate(dateTwo));
}

std::string CheckSameWeekDayResult(const DateYMD& dateOne, const DateYMD& dateTwo)
{
	if (dateOne.year != dateTwo.year)
	{
		return "ERROR";
	}
	auto dayСount = GetDatesDeltaInDays(dateOne, dateTwo);
	return dayСount % 7 == 0 ? "Same week day" : "Different week days";
}

std::string CheckSameWeekDay()
{
	// читаем даты из стандартного потока
	DateYMD dateOne = ReadDate();
	DateYMD dateTwo = ReadDate();

	// сравниваем, возвращаем результат
	return CheckSameWeekDayResult(dateOne, dateTwo);
}

int main()
{
	try
	{
		std::cout << CheckSameWeekDay() << '\n';
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << '\n';
		return 1;
	}
	return 0;
}
