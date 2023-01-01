#ifndef RECURRING_EVENT_H_
#define RECURRING_EVEMT_H_

#include "event_container.h"
#include "base_event.h"

namespace mtm {
	template<class EventType>
	class RecurringEvent : public EventContainer {
	public:
		RecurringEvent<EventType>(const DateWrap& first_date, const string& event_name,
						int num_occurences, int interval_days);
		RecurringEvent<EventType>(const RecurringEvent<EventType>& recurring_event);
		~RecurringEvent() = default;
		RecurringEvent<EventType>& operator=(const RecurringEvent<EventType>& recurring_event);
		void add(const BaseEvent& base_event) override;
	};

	template<class EventType>
	inline RecurringEvent<EventType>::RecurringEvent(
		const DateWrap& first_date, const string& event_name,
		int num_occurences, int interval_days) : EventContainer()
	{
		if (num_occurences <= 0) {
			throw InvalidNumber();
		}
		else if (interval_days <= 0) {
			throw InvalidInterval();
		}
		
		int inserted_num = 0;
		for (int i = 0; i < num_occurences; i++) {
			EventType event_type(first_date + (interval_days * inserted_num), event_name);
			BaseEvent* event_clone = event_type.clone();
			clones_arr.add(event_clone);
			event_container->insert(event_clone);
			inserted_num++;
		}
	}

	template<class EventType>
	inline RecurringEvent<EventType>::RecurringEvent(const RecurringEvent<EventType>& recurring_event) :
		EventContainer(recurring_event) {}

	template<class EventType>
	inline RecurringEvent<EventType>& RecurringEvent<EventType>::operator=
		(const RecurringEvent<EventType>& recurring_event)
	{
		if (this == &recurring_event) {
			return *this;
		}
		delete event_container;
		event_container = recurring_event.event_container;
		return *this;
	}

	template<class EventType>
	inline void RecurringEvent<EventType>::add(const BaseEvent& base_event)
	{
		throw NotSupported();
	}
}
#endif // RECURRING_EVENT_H_

