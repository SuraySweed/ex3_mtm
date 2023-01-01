#include "../partB/base_event.h"
#include "../partB/event_container.h"
#include "schedule.h"
#include "../partA/date_wrap.h"
#include <algorithm>
#include <iostream>

using mtm::Schedule;
using mtm::Exceptions;
using mtm::BaseEvent;
using mtm::EventContainer;
using mtm::DateWrap;
using std::find;
using std::cout;
using std::list;

bool Schedule::isEventInEventContainerinScheduke(const EventContainer& events) {
    for (ecIter ec_iter = events.begin(); ec_iter != events.end(); ++ec_iter) {
        for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
            if (**list_iter == *ec_iter) {
                return true;
            }
        }
    }
    return false;
}

bool Schedule::compareEvents(const BaseEvent* event1, const BaseEvent* event2)
{
    if (*event1 > *event2) return false;
    else {
        return true;
    }
}

Schedule::Schedule() : schedule() {}

mtm::Schedule::Schedule(const list<BaseEvent*>& other_schedule) : schedule(other_schedule) {}

mtm::Schedule::~Schedule()
{
    for (int i = 0; i < clones_arr.counter; i++) {
        delete clones_arr.clone_ptr[i];
    }
}

Schedule& Schedule::operator=(const list<BaseEvent*>& other_schedule) {
    schedule = other_schedule;
    return *this;
}

void mtm::Schedule::addEvents(const EventContainer& events) {
    if (isEventInEventContainerinScheduke(events)) {
        throw EventAlreadyExists();
    }
    //schedule.insert(schedule.begin(), events.begin(), events.end());
    for (ecIter ec_iter = events.begin(); ec_iter != events.end(); ++ec_iter) {
        BaseEvent* event_clone = (*ec_iter).clone();
        schedule.push_back(event_clone);
        clones_arr.add(event_clone);
    }
    schedule.sort(compareEvent);
}

void Schedule::registerToEvent(const DateWrap& date_wrap, const string& name, const int& student_id) {
    bool is_event_exist = false;
    for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
        if ((*list_iter)->getEventDate() == date_wrap && (*list_iter)->getEventName() == name) {
            /*
            try {
                (*list_iter)->registerParticipant(student_id);
            }
            catch (Exceptions& e) {
                throw e;
            }
            */
            (*list_iter)->registerParticipant(student_id);
            is_event_exist = true;
        }
    }
    if (!is_event_exist) {
        throw EventDoesNotExist();
    }
}

void Schedule::unregisterFromEvent(const DateWrap& date_wrap, const string& name, const int& student_id) {
    bool is_event_exist = false;
    for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
        if ((*list_iter)->getEventDate() == date_wrap && (*list_iter)->getEventName() == name) {
            try {
                (*list_iter)->unregisterParticipant(student_id);
            }
            catch (Exceptions& exception) {
                throw exception;
            }
            is_event_exist = true;
        }
    }
    if (!is_event_exist) {
        throw EventDoesNotExist();
    }
}

void Schedule::printAllEvents() const {
    for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
        (*list_iter)->printShort(cout);
        cout << "\n";
    }
}

void mtm::Schedule::printMonthEvents(const int& month, const int& year) const {
    for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
        if ((*list_iter)->getEventDate().month() == month &&
            (*list_iter)->getEventDate().year() == year) {
            (*list_iter)->printShort(cout);
            cout << "\n";
        }
    }
}

//void Schedule::printEventDetails(const string& name, const DateWrap& date_wrap) {
void Schedule::printEventDetails(const DateWrap& date_wrap, const string& name) const {
    bool is_event_exist = false;
    for (listIter list_iter = schedule.begin(); list_iter != schedule.end(); ++list_iter) {
        if ((*list_iter)->getEventDate() == date_wrap && (*list_iter)->getEventName() == name) {
            (*list_iter)->printLong(cout);
            cout << "\n";
            is_event_exist = true;
        }
    }
    if (!is_event_exist) {
        throw EventDoesNotExist();
    }
}
