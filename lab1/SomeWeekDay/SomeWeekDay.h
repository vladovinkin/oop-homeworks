#pragma once
#include <string>

struct DateYMD {
	std::size_t year;
	std::size_t month;
	std::size_t day;
};

struct Args {
	std::string fileName;
};

std::size_t GetMonthDaysNumber(std::size_t month, std::size_t year);
bool IsYearIntercalary(std::size_t year);
void CheckSameWeekDay(const std::string& fileName);
DateYMD ReadDatesFromStream(std::ifstream& input);
bool isDateCorrect(const DateYMD date);
void ShowSameWeekDayResult(const DateYMD dateOne, const DateYMD dateTwo);
std::size_t GetDatesDeltaInDays(DateYMD dateOne, DateYMD dateTwo);
