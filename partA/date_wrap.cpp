#include "date_wrap.h"

using std::cout;
using std::endl;
using mtm::DateWrap;

DateWrap::DateWrap(int const day, int const month, int const year) : current_day(day), current_month(month),
    current_year(year) 
{
    date = dateCreate(day, month, year);
    if (!date) {
        throw InvalidDate();
    }
}

DateWrap::DateWrap(const DateWrap& date_wrap) : current_day(date_wrap.current_day),
    current_month(date_wrap.current_month), current_year(date_wrap.current_year),
    date(dateCopy(date_wrap.date)) {}

DateWrap::~DateWrap() {
    dateDestroy(date);
}

int DateWrap::day() const {
    return current_day;
}

int DateWrap::month() const {
    return current_month;
}

int DateWrap::year() const {
    return current_year;
}

DateWrap& mtm::DateWrap::operator=(const DateWrap& date_wrap)
{
    if (this == &date_wrap) {
        return *this;
    }
    dateDestroy(date);
    date = dateCopy(date_wrap.date);
    current_day = date_wrap.current_day;
    current_month = date_wrap.current_month;
    current_year = date_wrap.current_year;
    return *this;
}

DateWrap DateWrap::operator++(int) {
    DateWrap temp(*this);
    dateTick(this->date);
    dateGet(this->date, &current_day, &current_month, &current_year);
    return temp;
}

DateWrap& DateWrap::operator+=(const int days) {
    if (days < 0) {
        throw NegativeDays();
    }

    Date new_date = dateCopy(this->date);
    for (int i = 0; i < days; i++) {
        dateTick(new_date);
    }
    dateDestroy(date);
    date = new_date;
    dateGet(new_date, &current_day, &current_month, &current_year);

    return *this;
}

void DateWrap::print(const DateWrap& date_wrap) {
    cout << date_wrap;
}

bool mtm::operator<(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return (date_wrap2 > date_wrap1);
}

bool mtm::operator>=(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return ((date_wrap1 > date_wrap2) || (date_wrap1 == date_wrap2));
}

bool mtm::operator<=(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return (!(date_wrap1 > date_wrap2));
}

bool mtm::operator!=(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return (!(date_wrap1 == date_wrap2));
}

DateWrap mtm::operator+(const DateWrap& date_wrap, const int day) {
    if (day < 0) {
        throw NegativeDays();
    }
    return (DateWrap(date_wrap) += day);
}

DateWrap mtm::operator+(const int day, const DateWrap& date_wrap) {
    if (day < 0) {
        throw NegativeDays();
    }
    return (DateWrap(date_wrap) += day);
}
