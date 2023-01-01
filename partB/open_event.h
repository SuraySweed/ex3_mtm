#ifndef OPEN_EVENT_H_
#define OPEN_EVENT_H_

#include "base_event.h"

namespace mtm {
    class OpenEvent : public BaseEvent {
        public:
            OpenEvent(const mtm::DateWrap& date, const string& name);
            OpenEvent(const OpenEvent& open_event);
            ~OpenEvent() = default;
            OpenEvent& operator=(const OpenEvent& open_event);
            BaseEvent* clone() const override; // copy students???
    };
}
#endif //OPEN_EVENT_H_
