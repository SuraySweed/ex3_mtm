#include "exceptions.h"

using mtm::Exceptions;
using mtm::InvalidDate;
using mtm::NegativeDays;

const string InvalidDate::what()
{
	return string("InvalidDate");
}

const string NegativeDays::what()
{
	return string("NegativeDays");
}
