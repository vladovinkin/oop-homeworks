#pragma once

// Месяц
enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

constexpr unsigned NonLeapYearDays = 365;
constexpr unsigned BaseYear = 1970;

constexpr unsigned DaysBeforeJanuary = 0;
constexpr unsigned DaysBeforeFebruary = DaysBeforeJanuary + 31;
constexpr unsigned DaysBeforeMarch = DaysBeforeFebruary + 28;
constexpr unsigned DaysBeforeApril = DaysBeforeMarch + 31;
constexpr unsigned DaysBeforeMay = DaysBeforeApril + 30;
constexpr unsigned DaysBeforeJune = DaysBeforeMay + 31;
constexpr unsigned DaysBeforeJuly = DaysBeforeJune + 30;
constexpr unsigned DaysBeforeAugust = DaysBeforeJuly + 31;
constexpr unsigned DaysBeforeSeptember = DaysBeforeAugust + 31;
constexpr unsigned DaysBeforeOctober = DaysBeforeSeptember + 30;
constexpr unsigned DaysBeforeNovember = DaysBeforeOctober + 31;
constexpr unsigned DaysBeforeDecember = DaysBeforeNovember + 30;

constexpr unsigned DaysToMonth[] = {
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

// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class CDate
{
public:
    // инициализируем дату заданными днем, месяцем и годом.
    // примечание: год >= 1970
    CDate(unsigned day, Month month, unsigned year);

    // инициализируем дату количеством дней, прошедших после 1 января 1970 года
    // например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
    explicit CDate(unsigned timestamp);

    // Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
    CDate();

    // возвращает день месяца (от 1 до 31)
    unsigned GetDay()const;

    // возвращает месяц
    Month GetMonth()const;

    // возвращает год
    unsigned GetYear()const;

    // возвращает день недели
    WeekDay GetWeekDay()const;

    // возвращает количество дней, прошедших с 1 января 1970 года
    unsigned GetDays()const;

    // оператор + (date + days)
    CDate operator +(unsigned days) const;

    // оператор ++ (префикс)
    CDate& operator ++();

    // оператор -- (префикс)
    CDate& operator --();

    // оператор ++ (постфикс)
    CDate operator ++(int);

    // оператор -- (постфикс)
    CDate operator --(int);

private:
    bool IsYearLeap(unsigned year)const;
    WeekDay IntToWeekDay(unsigned weekDayIndex)const;
    Month IntToMonth(unsigned month)const;
private:
    unsigned m_days;
};

//CDate operator +(unsigned days, CDate const& date)
//{
//    return CDate(days + date.GetDays());
//}
