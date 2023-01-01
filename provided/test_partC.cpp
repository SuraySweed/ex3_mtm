#include "base_event.h"
#include "closed_event.h"
#include "custom_event.h"
#include "date_wrap.h"
#include "event_container.h"
#include "exceptions.h"
#include "festival.h"
#include "one_time_event.h"
#include "open_event.h"
#include "recurring_event.h"
#include "schedule.h"
#include <cstdlib>
#include <iostream>

void test1(const mtm::Schedule& schedule) { schedule.printAllEvents(); }

void test2(const mtm::Schedule& schedule) {
    schedule.printEventDetails(mtm::DateWrap(27, 12, 2020), "Publish Test");
}

void test3(const mtm::Schedule& schedule) {
    schedule.printEventDetails(mtm::DateWrap(5, 1, 2021), "Update Q&A");
}

void test4(const mtm::Schedule& schedule) { schedule.printMonthEvents(12); }

class MutatingPredicate {
    int counter = 0;

public:
    bool operator()(const mtm::BaseEvent& event) {
        ++counter;
        return true;
    }
};

void test5(const mtm::Schedule& schedule) {
    schedule.printSomeEvents(MutatingPredicate(), true);
}

typedef void (*Test)(const mtm::Schedule&);
const Test tests[] = {test1, test2, test3, test4, test5};

int main(int argc, char* argv[]) {
    mtm::Schedule schedule;
    schedule.addEvents(mtm::OneTimeEvent<mtm::OpenEvent>(
        mtm::DateWrap(27, 12, 2020), "Publish Test"));

    mtm::RecurringEvent<mtm::ClosedEvent> closed(mtm::DateWrap(20, 12, 2020),
                                                 "Update Q&A", 6, 5);
    for (mtm::BaseEvent& event : closed) {
        mtm::ClosedEvent& closed_event = dynamic_cast<mtm::ClosedEvent&>(event);
        closed_event.addInvitee(1337);
        closed_event.addInvitee(850);
        closed_event.addInvitee(1500);
    }
    schedule.addEvents(closed);

    schedule.registerToEvent(mtm::DateWrap(20, 12, 2020), "Update Q&A", 850);
    schedule.registerToEvent(mtm::DateWrap(20, 12, 2020), "Update Q&A", 1500);
    schedule.registerToEvent(mtm::DateWrap(5, 1, 2021), "Update Q&A", 850);
    schedule.registerToEvent(mtm::DateWrap(5, 1, 2021), "Update Q&A", 1500);
    schedule.unregisterFromEvent(mtm::DateWrap(20, 12, 2020), "Update Q&A",
                                 1500);

    if (argc < 2) {
        test1(schedule);
        test2(schedule);
        test3(schedule);
        test4(schedule);
        test5(schedule);
    } else if (argc > 2) {
        std::cout << "invalid arguments" << std::endl;
    } else {
        int i = std::atoi(argv[1]);
        tests[i - 1](schedule);
    }
    return 0;
}
