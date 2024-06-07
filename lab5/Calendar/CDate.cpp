#include "CDate.h"

CDate::CDate(unsigned day, Month month, unsigned year)
{
	unsigned timestamp = (IsYearLeap(year) && month >= Month::MARCH) ? 1 : 0;
	timestamp += DaysToMonth[unsigned(month) - 1];
	timestamp += ((year - 1970) * 365 + (year - 1969) / 4 - (year - 1901) / 200);
	timestamp += day - 1;
	m_days = timestamp;
}

CDate::CDate(unsigned timestamp)
{
	m_days = timestamp;
}

CDate::CDate()
{
	m_days = 0;
}

unsigned CDate::GetDays()const
{
	return m_days;
}

WeekDay CDate::GetWeekDay()const
{
	return IntToWeekDay((m_days + 4) % 7);
}

bool CDate::IsYearLeap(unsigned year)const
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

WeekDay CDate::IntToWeekDay(unsigned weekDayIndex)const
{
	switch (weekDayIndex)
	{
		case 1: return WeekDay::MONDAY;
		case 2: return WeekDay::TUESDAY;
		case 3: return WeekDay::WEDNESDAY;
		case 4: return WeekDay::THURSDAY;
		case 5: return WeekDay::FRIDAY;
		case 6: return WeekDay::SATURDAY;
	}
	return WeekDay::SUNDAY;
}

Month CDate::IntToMonth(unsigned monthIndex)const
{
	switch (monthIndex)
	{
		case 2: return Month::FEBRUARY;
		case 3: return Month::MARCH;
		case 4: return Month::APRIL;
		case 5: return Month::MAY;
		case 6: return Month::JUNE;
		case 7: return Month::JULY;
		case 8: return Month::AUGUST;
		case 9: return Month::SEPTEMBER;
		case 10: return Month::OCTOBER;
		case 11: return Month::NOVEMBER;
		case 12: return Month::DECEMBER;
	}
	return Month::JANUARY;
}

CDate CDate::operator +(unsigned days)const
{
	return CDate(m_days + days);
}

/*
unsigned CDate::GetDay()const
{

}

Month CDate::GetMonth()const
{

}

unsigned CDate::GetYear()const
{

}

*/