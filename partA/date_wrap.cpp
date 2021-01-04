#include <iostream>
#include "date_wrap.h"

extern "C" {
    #include "date.h"
}

using std::cout;
using std::endl;
using mtm::DateWrap;

DateWrap::DateWrap(const int day, const int month, const int year) {
    date = dateCreate(day, month, year);
    if(!date) {
        throw InvalidDate();
    }
    current_day = day;
    current_month = month;
    current_year = year;
}  

DateWrap::DateWrap(const DateWrap& date_wrap) {
    current_day = date_wrap.day();
    current_month = date_wrap.month();
    current_year = date_wrap.year();
    date = dateCopy(date_wrap.date);
}

DateWrap::~DateWrap() {
    //dateDestroy(date);
    delete date;
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

DateWrap DateWrap::operator++(int) {
    dateTick(this->date);
    dateGet(this->date, &current_day, &current_month, &current_year);
    
    return *this;
}

DateWrap& DateWrap::operator+=(const int days) {
    if(days < 0) {
        throw NegativeDays();
    }

    Date new_date = dateCopy(this->date);
    for(int i = 0; i < days; i++) {
        dateTick(new_date);
    }

    dateDestroy(date);
    date = new_date;
    dateGet(new_date, &current_day, &current_month, &current_year);

    return *this;
}

/*
bool operator>(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return dateCompare();
}
*/
bool operator<(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return (date_wrap2 > date_wrap1);
}

bool operator>=(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return ((date_wrap1 > date_wrap2) || (date_wrap1 == date_wrap2));
}

bool operator<=(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
   return (!(date_wrap1 > date_wrap2)); 
}

bool operator!=(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
    return (!(date_wrap1 == date_wrap2));
}

DateWrap operator+(const DateWrap& date_wrap, const int day) {
    if (day < 0) {
        throw NegativeDays();
    }
    return (DateWrap(date_wrap) += day);
}

