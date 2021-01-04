#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>
#include <exception>

using std::exception;
using std::string;

class Exceptions : public exception
{
	public:
		Exceptions(string message);
		string what(); //override

	private:
		string error_message;
};

class InvalidDate : Exceptions {
	InvalidDate(string message)
};

#endif; //EXCEPTIONS_H