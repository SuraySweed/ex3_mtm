#ifndef DATE_WRAP_H_
#define DATE_WRAP_H_

#include <iostream>
#include <string>
#include "date.h"
#include "exceptions.h"

using std::ostream;

namespace mtm {
    class DateWrap {
        private:
            Date date;
            int current_day, current_month, current_year;        
        
        public:
            DateWrap(const int day, const int month, const int year);
            DateWrap(const DateWrap& date_wrap); // copy constructor
            ~DateWrap();
            int day() const;
            int month() const;
            int year() const;
            DateWrap operator++(int); // ask dor!!!!
            DateWrap& operator+=(const int days);
            friend ostream&  operator<<(ostream&, const DateWrap&);
            friend bool operator>(const DateWrap&, const DateWrap&);
            friend bool operator==(const DateWrap&, const DateWrap&);

    };

    ostream&  operator<<(ostream& os, const DateWrap& date_wrap) {
        os << date_wrap.day() << '/' << date_wrap.month() << '/' << date_wrap.year();    
    }

    bool operator>(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
        return (dateCompare(date_wrap1.date, date_wrap2.date) > 0 ? true : false);
    }

    bool operator==(const DateWrap& date_wrap1, const DateWrap& date_wrap2) {
        return (dateCompare(date_wrap1.date, date_wrap2.date) == 0);
    }

    bool operator<(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    bool operator>=(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    bool operator<=(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    bool operator!=(const DateWrap& date_wrap1, const DateWrap& date_wrap2);
    DateWrap operator+(const DateWrap& date_wrap, const int day);
}
#endif //DATE_WRAP_H_
