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

	class RegistrationBlocked : public Exceptions {
		public:
			RegistrationBlocked() = default;
			const string what();
	};

	class AlreadyRegistered : public Exceptions {
		public:
			AlreadyRegistered() = default;
			const string what();
	};

	class NotRegistered : public Exceptions {
		public:
			NotRegistered() = default;
			const string what();
	};

	class AlreadyInvited : public Exceptions {
		public:
			AlreadyInvited() = default;
			const string what();
	};

	class NotSupported : public Exceptions {
		public:
			NotSupported() = default;
			const string what();
	};

	class InvalidStudent : public Exceptions {
	public:
		InvalidStudent() = default;
		const string what();
	};

	class DateMismatch : public Exceptions {
		public:
			DateMismatch() = default;
			const string what();
	};

	class InvalidNumber : public Exceptions {
		public:
			InvalidNumber() = default;
			const string what();
	};

	class InvalidInterval : public Exceptions {
		public:
			InvalidInterval() = default;
			const string what();
	};

	class EventAlreadyExists : public Exceptions {
		public:
			EventAlreadyExists() = default;
			const string what();
	};

	class EventDoesNotExist : public Exceptions {
		public:
			EventDoesNotExist() = default;
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