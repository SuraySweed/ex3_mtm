#ifndef DATE_WRAP_H_
#define DATE_WRAP_H_

#include <iostream>
#include <string>
#include "exceptions.h"

extern "C" {
#include "date.h"
}

using std::ostream;

namespace mtm {
    class DateWrap {
    private:
        Date date;
        int current_day, current_month, current_year;

    public:
        DateWrap(int const day, int const month, int const year);
        DateWrap(const DateWrap& date_wrap); // copy constructor
        ~DateWrap();
        int day() const;
        int month() const;
        int year() const;
        DateWrap operator++(int); 
        DateWrap& operator+=(const int days);
        friend ostream& operator<<(ostream& os, const DateWrap& date_wrap) {
            return os << date_wrap.day() << '/' << date_wrap.month() << '/' << date_wrap.year();
        }
        void print(const DateWrap& date_wrap);
        friend bool operator>(const DateWrap&, const DateWrap&);
        friend bool operator==(const DateWrap&, const DateWrap&);
    };

      

    bool operator<(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    bool operator>=(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    bool operator<=(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    bool operator!=(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    DateWrap operator+(const DateWrap& date_wrap, const int day);
    DateWrap operator+(const int day, const DateWrap& date_wrap);
}
#endif //DATE_WRAP_H_
