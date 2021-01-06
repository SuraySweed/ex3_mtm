#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>
#include <exception>

using std::exception;
using std::string;

namespace mtm {
	class Exceptions : public exception {};
	
	class InvalidDate : public Exceptions {
	public:
		InvalidDate() = default;
		const string what();
	};

	class NegativeDays : public Exceptions {
	public:
		NegativeDays() = default;
		const string what();
	};



	/*
	public:
		Exceptions(string message);
		string what(); //override

	private:
		string error_message;
	};
	*/
}


#endif //EXCEPTIONS_H