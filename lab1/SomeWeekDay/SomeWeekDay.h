#pragma once
#include <string>

struct DateYMD {
	int year;
	int month;
	int day;
};

struct Args {
	std::string dateOne;
	std::string dateTwo;
};

int GetMonthDaysNumber(int month, int year);
bool IsYearIntercalary(int year);