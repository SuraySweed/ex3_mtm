#ifndef CUSTOM_EVENT_H_
#define CUSTOM_EVENT_H_

#include <iostream>
#include <string>
#include "base_event.h"

namespace mtm {
    template<class CanRegister>
    class CustomEvent : public BaseEvent {
    private:
        CanRegister registration_condition;
    
    public:
        CustomEvent<CanRegister>(const mtm::DateWrap& date, const string& name, const CanRegister& condition);
        CustomEvent(const CustomEvent& event); 
        ~CustomEvent() = default;
        CustomEvent<CanRegister>& operator=(const CustomEvent<CanRegister>& custom_event);
        void registerParticipant(const int student_id) override;
        BaseEvent* clone() const override;
    };

    template<class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const DateWrap& date, const string& name,
        const CanRegister& condition) : BaseEvent(date, name), registration_condition(condition) {}

    template <class CanRegister>
    CustomEvent<CanRegister>::CustomEvent(const CustomEvent<CanRegister>& event) : BaseEvent(event),
        registration_condition(event.registration_condition) {}

    template<class CanRegister>
    inline CustomEvent<CanRegister>& CustomEvent<CanRegister>::operator=(const CustomEvent<CanRegister>& custom_event)
    {
        if (this == &custom_event) {
            return *this;
        }
        delete students;

        event_name = custom_event.event_name;
        students = custom_event.students;
        date_wrap = custom_event.date_wrap;
        registration_condition = custom_event.registration_condition;

        return *this;
    }

    template<class CanRegister>
    void CustomEvent<CanRegister>::registerParticipant(const int student_id) {
        if (student_id > MAX_NUMBER || student_id < MIN_NUMBER)
        {
            throw InvalidStudent();
        }

        else if(!(registration_condition(student_id))) {
            throw RegistrationBlocked();
        }

        else if (this->students->isElementInLinkedList(student_id))
        {
            throw AlreadyRegistered();
        }

        this->students->insert(student_id);
    }

    template<class CanRegister>
    BaseEvent* CustomEvent<CanRegister>::clone() const {
        return new CustomEvent(*this);
    }
}

#endif //CUSTOM_EVENT_H_
