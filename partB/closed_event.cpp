#include "closed_event.h"

using mtm::BaseEvent;
using mtm::ClosedEvent;
using mtm::DateWrap;

ClosedEvent::ClosedEvent(const DateWrap& date, const string& name) : BaseEvent(date, name),
    invited(new PriorityLinkedList<int, CompareStudents>(CompareStudents())) {}
 

mtm::ClosedEvent::ClosedEvent(const ClosedEvent& closed_event) : BaseEvent(closed_event)
    , invited(new PriorityLinkedList<int, CompareStudents>(*(closed_event.invited))) {}


mtm::ClosedEvent::~ClosedEvent()
{
    delete invited;
}

ClosedEvent& ClosedEvent::operator=(const ClosedEvent& closed_event)
{
    if (this == &closed_event) {
        return *this;
    }
    delete students;
    delete invited;

    date_wrap = closed_event.date_wrap;
    event_name = closed_event.event_name;
    students = closed_event.students;
    invited = closed_event.invited;

    return *this;
}


void ClosedEvent::addInvitee(const int student_id) {
    if (student_id > MAX_NUMBER || student_id < MIN_NUMBER)
    {
        throw InvalidStudent();
    }

    if (this->invited->isElementInLinkedList(student_id)) {
        throw AlreadyInvited();
    }

    this->invited->insert(student_id);
}

void ClosedEvent::registerParticipant(const int student_id) {
    if (student_id > MAX_NUMBER || student_id < MIN_NUMBER)
    {
        throw InvalidStudent();
    }

    if (this->students->isElementInLinkedList(student_id))
    {
        throw AlreadyRegistered();
    }

    if (!(this->invited->isElementInLinkedList(student_id))) {
        throw RegistrationBlocked();
    }

    this->students->insert(student_id);
}

BaseEvent* ClosedEvent::clone() const {
    //return Unique_ptr(ClosedEvent(*this));
    return new ClosedEvent(*this);
}

