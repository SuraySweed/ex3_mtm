#include "date.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_DAY 30
#define MIN_DAY 1
#define MAX_MONTH 12
#define MIN_MONTH 1
#define DAYS_IN_YEAR 365
#define POSTIVE_NUMBER 1
#define NEGATIVE_NUMBER -1
#define ZERO 0


/* type for defining the date*/
struct Date_t {
    int day;
    int month;
    int year;
};

//checks if the day is valid 
static bool isDayValid(int day)
{
    return (day >= MIN_DAY && day <= MAX_DAY);
}

//checks if the month is valid
static bool isMonthValid(int month)
{
    return (month >= MIN_MONTH && month <= MAX_MONTH);
}

//checks if the date is valid
static bool isDateValid(Date date)
{
    assert(date != NULL);
    return (isMonthValid(date->month) && isDayValid(date->day));
}

//returns the amount of days in of the date
static int dateToDays(Date date)
{
    assert(date != NULL);
    return (date->day + ((date->month) * (MAX_DAY - MIN_DAY + 1)) + (DAYS_IN_YEAR * (date->year)));
}

//returns the difference in days of tow given dates 
static int dateDifference(Date date1, Date date2)
{
    assert(isDateValid(date1) && isDateValid(date2));

    int days1 = dateToDays(date1);
    int days2 = dateToDays(date2);

    return days1 - days2;
}

//creates new date
Date dateCreate(int day, int month, int year)
{
    if (!isDayValid(day) || !isMonthValid(month))
    {
        return NULL;
    }

    Date date = malloc(sizeof(*date));

    if (!date)
    {
        return NULL;
    }

    date->day = day;
    date->month = month;
    date->year = year;

    if (!(isDateValid(date)))
    {
        return NULL;
    }

    return date;
}

//destroys the date
void dateDestroy(Date date)
{
    if (!date)
    {
        return;
    }

    free(date);
}

//copies the date
Date dateCopy(Date date)
{
    if (!date)
    {
        return NULL;
    }

    return dateCreate(date->day, date->month, date->year);
}

//fills the date with given values and return true if success 
bool dateGet(Date date, int* day, int* month, int* year)
{
    if (!date || !day || !month || !year)
    {
        return false;
    }

    *day = date->day;
    *month = date->month;
    *year = date->year;

    return true;
}

//compares two dates and returns positive if the first one is greater, zero if equal and negative otherwise
int dateCompare(Date date1, Date date2)
{
    int date_diffrence = 0;

    if (!date1 || !date2)
    {
        return ZERO;
    }
    assert(isDateValid(date1) && isDateValid(date2));

    date_diffrence = dateDifference(date1, date2);

    if (date_diffrence == ZERO)
    {
        return ZERO;
    }

    return date_diffrence > ZERO ? POSTIVE_NUMBER : NEGATIVE_NUMBER;
}

//adds one day to the date
void dateTick(Date date)
{
    if (!date)
    {
        return;
    }

    assert(isDateValid(date));

    if (date->day < MAX_DAY)
    {
        date->day = date->day + 1;
    }

    else if (date->day == MAX_DAY && date->month < MAX_MONTH)
    {
        date->day = 1;
        date->month = date->month + 1;
    }

    else if (date->day == MAX_DAY && date->month == MAX_MONTH)
    {
        date->day = 1;
        date->month = 1;
        date->year = date->year + 1;
    }
}
