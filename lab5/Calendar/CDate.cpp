#include "CDate.h"
#include <string>

// добавить проверку на ввод невалидной даты
CDate::CDate(unsigned day, Month month, unsigned year)
{
	unsigned timestamp = (IsYearLeap(year) && month >= Month::MARCH) ? 1 : 0;

	// использовать проверенный индекс (+)
	unsigned dayToMonthIdx = unsigned(month) - 1;
	timestamp += DaysToMonth[dayToMonthIdx];

	// некорректно определяется високосный год (+)
	timestamp += ((year - BaseYear) * NonLeapYearDays + (year - 1969) / 4 + (year - 1601) / 400) - (year - 1901) / 100;
	timestamp += day - 1;
	m_days = timestamp;
}

CDate::CDate(unsigned timestamp)
{
	m_days = static_cast<int>(timestamp);
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

bool IsYearLeap(unsigned year)
{
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

WeekDay CDate::IntToWeekDay(unsigned weekDayIndex)const
{
	switch (weekDayIndex)
	{
		case 0: return WeekDay::SUNDAY;
		case 1: return WeekDay::MONDAY;
		case 2: return WeekDay::TUESDAY;
		case 3: return WeekDay::WEDNESDAY;
		case 4: return WeekDay::THURSDAY;
		case 5: return WeekDay::FRIDAY;
		case 6: return WeekDay::SATURDAY;
	}
	return WeekDay::NO_WEEKDAY;
}

Month IntToMonth(unsigned monthIndex)
{
	switch (monthIndex)
	{
		case 1: return Month::JANUARY;
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
	return Month::NO_MONTH;
}

unsigned CDate::GetDay()const
{
	unsigned year = GetYear();
	unsigned daysRemind = m_days - (((year - BaseYear) * NonLeapYearDays + (year - 1969) / 4 + (year - 1601) / 400) - (year - 1901) / 100);
	unsigned leapDay = IsYearLeap(year) ? 1 : 0;
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
	unsigned year = GetYear();
	unsigned daysRemind = m_days - (((year - BaseYear) * NonLeapYearDays + (year - 1969) / 4 + (year - 1601) / 400) - (year - 1901) / 100);
	unsigned leapDay = IsYearLeap(year) ? 1 : 0;
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
	return IntToMonth(monthNum + 1);
}

unsigned CDate::GetYear()const
{
	return BaseYear + ((m_days - (LeapYearsInRange(m_days / NonLeapYearDays))) / NonLeapYearDays);
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

unsigned CDate::operator -(const CDate& date) const
{
	unsigned dateDays = date.GetDays();
	return m_days > dateDays
		? m_days - dateDays
		: dateDays - m_days;
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
		<< date.GetYear();
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

unsigned LeapYearsInRange(unsigned years)
{
	return years / 4 - years / 100 + years / 400;
}
