#ifndef CLOSED_EVENT_H_
#define CLOSED_EVENT_H_

#include "base_event.h"

namespace mtm {
    class ClosedEvent : public BaseEvent {
    private:
        PriorityLinkedList<int, CompareStudents>* invited;

    public:
        ClosedEvent(const mtm::DateWrap& date, const string& name);
        ClosedEvent(const ClosedEvent& closed_event);
        ~ClosedEvent();
        ClosedEvent& operator=(const ClosedEvent& closed_event);
        void addInvitee(const int student_id);
        void registerParticipant(const int student_id) override;
        BaseEvent* clone() const override;
    };
}
#endif //CLOSED_EVENT_H_