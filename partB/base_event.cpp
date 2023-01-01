#include "base_event.h"

using mtm::BaseEvent;
using mtm::DateWrap;
using mtm::PriorityLinkedList;
using std::ostream;

BaseEvent::BaseEvent(const DateWrap& date, const string& name) : date_wrap(date), event_name(name),
    students(new PriorityLinkedList<int, CompareStudents>(CompareStudents())) {}

BaseEvent::BaseEvent(const BaseEvent& base_event) : date_wrap(base_event.date_wrap),
    event_name(base_event.event_name), 
    students(new PriorityLinkedList<int, CompareStudents>(*(base_event.students))) {}


mtm::BaseEvent::~BaseEvent()
{
    delete students;
}

const DateWrap& mtm::BaseEvent::getEventDate() const
{
    return date_wrap;
}

const string& mtm::BaseEvent::getEventName() const 
{
    return event_name;
}

BaseEvent& BaseEvent::operator=(const BaseEvent& base_event)
{
    if (this == &base_event) {
        return *this;
    }

    delete students;

    date_wrap = base_event.date_wrap;
    students = base_event.students;
    event_name = base_event.event_name;
    return *this;
}

ostream& mtm::BaseEvent::printShort(ostream& os)
{
    return os << event_name << ' ' << date_wrap << "\n"; 
}

ostream& mtm::BaseEvent::printLong(ostream& os)
{
    os << event_name << ' ' << date_wrap << '\n';
    int size = students->getSize();
    if (size >= 1) {
        int student_id = students->getFirst(*students);
        os << student_id << '\n';
        for (int i = 0; i < size - 1; i++) {
            student_id = students->getNext(*students);
            os << student_id << '\n';
        }
    }
    return os;
}

void BaseEvent::registerParticipant(const int student_id) {
    if (student_id > MAX_NUMBER || student_id < MIN_NUMBER)
    {
        throw InvalidStudent();
    }

    if (this->students->isElementInLinkedList(student_id))
    {
        throw AlreadyRegistered();
    }

    this->students->insert(student_id);
}

void BaseEvent::unregisterParticipant(const int student_id) {
    if (student_id > MAX_NUMBER || student_id < MIN_NUMBER)
    {
        throw InvalidStudent();
    }

    if (!(students->isElementInLinkedList(student_id)))
    {
        throw NotRegistered();
    }

    this->students->deleteNodeByElement(student_id);
}

bool mtm::operator>(const BaseEvent& event1, const BaseEvent& event2) {
    return (!(event1 <= event2));
}

bool mtm::operator!=(const BaseEvent& event1, const BaseEvent& event2)
{
    return (!(event1 == event2));
}

