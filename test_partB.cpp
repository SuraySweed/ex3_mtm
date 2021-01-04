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
#include <cstdlib>
#include <iostream>

typedef mtm::EventContainer::EventIterator Iter;

void printEventsShort(mtm::EventContainer& events) {
    for (Iter iter = events.begin(); iter != events.end(); ++iter) {
        mtm::BaseEvent& event = *iter;
        event.printShort(std::cout);
    }
}

void test1() {
    mtm::Festival festival(mtm::DateWrap(21, 10, 2020));
    festival.add(mtm::OpenEvent(mtm::DateWrap(21, 10, 2020), "Performance 1"));
    mtm::ClosedEvent closed(mtm::DateWrap(21, 10, 2020), "Performance 2");
    closed.addInvitee(1);
    closed.addInvitee(500);
    festival.add(closed);
    printEventsShort(festival);

    mtm::RecurringEvent<mtm::OpenEvent> recurring(mtm::DateWrap(21, 10, 2020),
                                                  "Wednesday Noon", 13, 7);
    printEventsShort(recurring);

    mtm::OneTimeEvent<mtm::OpenEvent> one_time(mtm::DateWrap(2, 3, 80),
                                               "A long time ago");
    printEventsShort(one_time);
}

void test2_aux(mtm::BaseEvent& event) {
    event.registerParticipant(1);
    event.registerParticipant(20000);
    event.unregisterParticipant(1);
    event.registerParticipant(3);
    mtm::BaseEvent* clone = event.clone();
    clone->printShort(std::cout);
    clone->printLong(std::cout);
    delete clone;
}

struct StudentFilter {
    bool operator()(int student) {
        return student == 1 || student == 3 || student == 20000;
    }
};

void test2() {
    mtm::OpenEvent open(mtm::DateWrap(21, 10, 2020), "An Open Event");
    test2_aux(open);
    mtm::ClosedEvent closed(mtm::DateWrap(21, 10, 2020), "A Closed Event");
    closed.addInvitee(1);
    closed.addInvitee(3);
    closed.addInvitee(20000);
    test2_aux(closed);
    mtm::CustomEvent<StudentFilter> custom(mtm::DateWrap(21, 10, 2020),
                                           "A Custom Event", StudentFilter());
    test2_aux(custom);
}

typedef void (*Test)();
const Test tests[] = {test1, test2};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        test1();
        test2();
    } else if (argc > 2) {
        std::cout << "invalid arguments" << std::endl;
    } else {
        int i = std::atoi(argv[1]);
        tests[i - 1]();
    }
    return 0;
}
