#ifndef ONE_TIME_EVENT_H_
#define ONE_TIME_EVENT_H_

#include "event_container.h"

namespace mtm {
	template<class EventType>
	class OneTimeEvent : public EventContainer {
	private:
		EventType* event_type;
	public:
		OneTimeEvent<EventType>(const mtm::DateWrap& date, const string& name);
		OneTimeEvent<EventType>(const OneTimeEvent<EventType>& one_time_event);
		~OneTimeEvent();
		OneTimeEvent<EventType>& operator=(const OneTimeEvent<EventType>& one_time_event);
		void add(const BaseEvent& base_event) override;
	};

	template<class EventType>
	inline OneTimeEvent<EventType>::OneTimeEvent(const mtm::DateWrap& date, const string& name) : EventContainer()
	{
		event_type = new EventType(date, name);
		event_container->insert(event_type);
	}

	template<class EventType>
	inline OneTimeEvent<EventType>::OneTimeEvent(const OneTimeEvent<EventType>& one_time_event) :
		EventContainer(one_time_event) {}

	template<class EventType>
	inline OneTimeEvent<EventType>::~OneTimeEvent()
	{
		delete event_type;
	}

	template<class EventType>
	inline OneTimeEvent<EventType>& OneTimeEvent<EventType>::operator=(const OneTimeEvent<EventType>& one_time_event)
	{
		if (this == &one_time_event) {
			return *this;
		}
		delete event_container;
		event_container = one_time_event.event_container;
		return *this;
	}

	template<class EventType>
	inline void OneTimeEvent<EventType>::add(const BaseEvent& base_event)
	{
		throw NotSupported();
	}
}
#endif // ONE_TIME_EVENT_H_

