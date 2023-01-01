#include "date_wrap.h"
#include "exceptions.h"
#include <iostream>

using mtm::DateWrap;
using std::cout;
using std::endl;

template <class T> void print(const T& x) { cout << x << endl; }


int main() {


    print("------staff testing------\n");
    DateWrap date(30, 11, 2020);
    print(date);
    print(date + 4);
    print(3 + date);
    date++;
    print(date);
    date += 7;
    print(date);
    print(date > DateWrap(29, 11, 2020));
    print(date <= DateWrap(29, 11, 2020));
    print(date == DateWrap(30, 11, 2020));
    print(date == DateWrap(8, 12, 2020));

    try {
        date += (-3);
    } catch (mtm::NegativeDays& ex) {
        print(ex.what());
    }
    try {
        date = date + (-3);
    } catch (mtm::NegativeDays& ex) {
        print(ex.what());
    }

    print("\n--------our tests-------\n");
    try {
        DateWrap date(-1, 15, 205);
    }
    catch (mtm::InvalidDate& ex) {
        print(ex.what());
    }
    
    DateWrap our_date(30, 12, 2020);
    print(our_date);
    our_date++;
    print(our_date);

    print(our_date < DateWrap(2, 1, 2021));
    print(5 + our_date);
    print(our_date + 5);

    return 0;
}
