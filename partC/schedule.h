#ifndef SCHEDULE_H_
#define SCHEDULE_H_

#include "../partB/event_container.h"
#include "../partB/base_event.h"
#include <list>
#include <iostream>
#include "../partB/clones_array.h"

typedef mtm::EventContainer::EventIterator ecIter;
typedef std::list<mtm::BaseEvent*>::const_iterator listIter;

namespace mtm {
	class Schedule {
	private:
		class CompareEvents {
		public:
			bool operator()(const mtm::BaseEvent* event1, const mtm::BaseEvent* event2) {
				if (*event1 > *event2) return false;
				return true;
			}
		};
		std::list<mtm::BaseEvent*> schedule;
		CompareEvents compareEvent;
		ClonesArray clones_arr;
		bool isEventInEventContainerinScheduke(const mtm::EventContainer& events);
		bool compareEvents(const mtm::BaseEvent* event1, const mtm::BaseEvent* event2);
	public:
		Schedule();
		Schedule(const std::list<mtm::BaseEvent*>& other_schedule);
		~Schedule();
		Schedule& operator=(const std::list<mtm::BaseEvent*>& other_schedule);
		void addEvents(const mtm::EventContainer& events);
		void registerToEvent(const mtm::DateWrap& date_wrap, const string& name, const int& student_id);
		void unregisterFromEvent(const mtm::DateWrap& date_wrap, const string& name, const int& student_id);
		void printAllEvents() const;
		void printMonthEvents(const int& month, const int& year) const;

		template<class Predicate>
		void printSomeEvents(Predicate predicate, bool verbose = false) const {
			for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
				if (predicate((**list_iter)) == true) {
					if (verbose) {
						(*list_iter)->printLong(std::cout);
					}
					else {
						(*list_iter)->printShort(std::cout);
					}
					std::cout << "\n";
				}
			}
		}
		void printEventDetails(const mtm::DateWrap& date_wrap, const string& name) const;
	};
}
#endif //SCHEDULE_H_
