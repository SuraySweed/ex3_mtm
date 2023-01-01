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

const string mtm::RegistrationBlocked::what()
{
	return string("RegistrationBlocked");
}

const string mtm::AlreadyRegistered::what()
{
	return string("AlreadyRegistered");
}

const string mtm::NotRegistered::what()
{
	return string("NotRegistered");
}

const string mtm::AlreadyInvited::what()
{
	return string("AlreadyInvited");
}

const string mtm::NotSupported::what()
{
	return string("NotSupported");
}

const string mtm::InvalidStudent::what()
{
	return string("InvalidStudent");
}

const string mtm::DateMismatch::what()
{
	return string("DateMismatch");
}

const string mtm::InvalidNumber::what()
{
	return string("InvalidNumber");
}

const string mtm::InvalidInterval::what()
{
	return string("InvalidInterval");
}

const string mtm::EventAlreadyExists::what()
{
	return string("EventAlreadyExists");
}

const string mtm::EventDoesNotExist::what()
{
	return string("EventDoesNotExist");
}
