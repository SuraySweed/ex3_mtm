#include <string>
#include "open_event.h"

using mtm::DateWrap;
using mtm::BaseEvent;
using mtm::OpenEvent;

OpenEvent::OpenEvent(const DateWrap& date, const string& name) : BaseEvent(date, name) {}

OpenEvent::OpenEvent(const OpenEvent& open_event) : BaseEvent(open_event) {}
    
OpenEvent& OpenEvent::operator=(const OpenEvent& open_event)
{
    if (this == &open_event) {
        return* this;
    }
    delete students;
    students = open_event.students;
    date_wrap = open_event.date_wrap;
    event_name = open_event.event_name;
    return *this;
}

BaseEvent* OpenEvent::clone() const {
    return new OpenEvent(*this);
}












