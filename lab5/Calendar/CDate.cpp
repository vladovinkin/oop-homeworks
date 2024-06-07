#include "CDate.h"
#include <string>

// добавить проверку на ввод невалидной даты
CDate::CDate(unsigned day, Month month, unsigned year)
{
	unsigned timestamp = (IsYearLeap(year) && month >= Month::MARCH) ? 1 : 0;
	// тспользовать проверенный индекс
	timestamp += DaysToMonth[unsigned(month) - 1];
	// некорректно определяется високосный год
	timestamp += ((year - BaseYear) * NonLeapYearDays + (year - 1969) / 4 - (year - 1901) / 200);
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
	return (year % 200 == 0) || ((year % 4 == 0) && (year % 100 != 0));
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

Month IntToMonth(unsigned monthIndex)
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

unsigned CDate::GetDay()const
{
	unsigned daysRemind = m_days;
	unsigned year = BaseYear;
	unsigned leapDay = IsYearLeap(year) ? 1 : 0;
	while (daysRemind >= (NonLeapYearDays + leapDay))
	{
		daysRemind -= (NonLeapYearDays + leapDay);
		year++;
		leapDay = IsYearLeap(year) ? 1 : 0;
	}
	unsigned monthNum;
	unsigned daysToMonthReal;
	for (monthNum = 11; monthNum > 0; monthNum--)
	{
		daysToMonthReal = DaysToMonth[monthNum] + (monthNum > 1 ? leapDay : 0);
		if (daysRemind > daysToMonthReal)
		{
			break;
		}
	}
	daysToMonthReal = DaysToMonth[monthNum] + (monthNum > 1 ? leapDay : 0);
	return daysRemind - daysToMonthReal + 1;
}

Month CDate::GetMonth()const
{
	unsigned daysRemind = m_days;
	unsigned year = BaseYear;
	unsigned leapDay = IsYearLeap(year) ? 1 : 0;
	while (daysRemind >= (NonLeapYearDays + leapDay))
	{
		daysRemind -= NonLeapYearDays + leapDay;
		year++;
		leapDay = IsYearLeap(year) ? 1 : 0;
	}
	unsigned monthNum;
	for (monthNum = 11; monthNum > 0; monthNum--)
	{
		if (daysRemind > (DaysToMonth[monthNum] + leapDay))
		{
			break;
		}
	}
	return IntToMonth(monthNum + 1);
}

unsigned CDate::GetYear()const
{
	unsigned daysRemind = m_days;
	unsigned year = BaseYear;
	unsigned leapDay = IsYearLeap(year) ? 1 : 0;
	while (daysRemind >= (NonLeapYearDays + leapDay))
	{
		daysRemind -= NonLeapYearDays + leapDay;
		year++;
		leapDay = IsYearLeap(year) ? 1 : 0;
	}
	return year;
}

CDate& CDate::operator ++()
{
	m_days += 1;
	return *this;
}

CDate& CDate::operator --()
{
	m_days -= 1;
	return *this;
}

CDate CDate::operator ++(int)
{
	CDate copy{ *this };
	++(*this);
	return copy;
}

CDate CDate::operator --(int)
{
	CDate copy{ *this };
	--(*this);
	return copy;
}

CDate CDate::operator +(unsigned days)const
{
	return CDate(m_days + days);
}

CDate operator +(unsigned days, CDate const& date)
{
    return date + days;
}

CDate CDate::operator -(unsigned days)const
{
	return CDate(m_days - days);
}

CDate CDate::operator +=(unsigned days)
{
	m_days += days;
	return *this;
}

CDate CDate::operator -=(unsigned days)
{
	m_days -= days;
	return *this;
}

std::ostream& operator <<(std::ostream& stream, CDate const& date)
{
	stream << TwoDigitFormatUnsigned(date.GetDay()) << "."
		<< TwoDigitFormatUnsigned((unsigned)date.GetMonth()) << "."
		<< TwoDigitFormatUnsigned(date.GetYear());
	return stream;
}

std::istream& operator >>(std::istream& stream, CDate& date)
{
	unsigned day = 0;
	unsigned month = 0;
	unsigned year = 0;

	if (
		(stream >> day) && (stream.get() == '.')
		&& (stream >> month) && (stream.get() == '.')
		&& (stream >> year)
		)
	{
		date = CDate(day, IntToMonth(month), year);
	}
	else
	{
		stream.setstate(std::ios_base::failbit | stream.rdstate());
	}

	return stream;
}


std::string TwoDigitFormatUnsigned(unsigned number)
{
	return (number < 10 ? "0" : "") + std::to_string(number);
}
