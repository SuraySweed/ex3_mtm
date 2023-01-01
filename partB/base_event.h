#ifndef BASE_EVENT_H_
#define BASE_EVENT_H_

#include <iostream>
#include <string>
#include "../partA/exceptions.h"
#include "../partA/date_wrap.h"
#include "priority_linked_list.h"

const int MAX_NUMBER = 1234567890;
const int MIN_NUMBER = 1;

namespace mtm {
    class BaseEvent {
    protected:
        class CompareStudents {
        public:
            int operator()(const int student1, const int student2) {
                if (student1 == student2) return ZERO;
                else if (student1 <= student2) return POSITIVE;
                else return NEGATIVE;
            }
        };
        DateWrap date_wrap;
        string event_name;
        PriorityLinkedList<int, CompareStudents>* students;

    public:
        BaseEvent(const DateWrap& date, const string& name);
        BaseEvent(const BaseEvent& base_event); 
        virtual ~BaseEvent(); //ask in resception hour  
           
        const DateWrap& getEventDate() const;
        const string& getEventName() const;
        virtual void registerParticipant(const int student_num);
        virtual void unregisterParticipant(const int student_num);
        virtual BaseEvent* clone() const = 0;

        BaseEvent& operator=(const BaseEvent&);

        std::ostream& printShort(std::ostream& os);
        std::ostream& printLong(std::ostream& os);

        
        friend bool operator==(const BaseEvent& event1, const BaseEvent& event2){
            return ((event1.date_wrap == event2.date_wrap) && (event1.event_name == event2.event_name));
        }

        friend bool operator<=(const BaseEvent& event1, const BaseEvent& event2) {
            if (event1.date_wrap == event2.date_wrap) {
                return (event1.event_name < event2.event_name);
            }
            else {
                return (event1.date_wrap < event2.date_wrap);
            }
        }
    };

    bool operator>(const BaseEvent& event1, const BaseEvent& event2);
    bool operator!=(const BaseEvent& event1, const BaseEvent& event2);
}

#endif //BASE_EVENT_H_

