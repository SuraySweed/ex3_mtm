#include "festival.h"
#include "clones_array.h"
#include "base_event.h"

using mtm::Festival;
using mtm::ClonesArray;
using mtm::BaseEvent;

mtm::Festival::Festival(const DateWrap& _date) : EventContainer(), date(_date) {}
mtm::Festival::Festival(const Festival& festival) : EventContainer(festival) , date(festival.date) {}

Festival& mtm::Festival::operator=(const Festival& festival)
{
	if (this == &festival) {
		return *this;
	}
	delete event_container;
	date = festival.date;
	event_container = festival.event_container;
	return *this;
}

void Festival::add(const BaseEvent& base_event) 
{
	if (date != base_event.getEventDate()) {
		throw DateMismatch();
	}
	BaseEvent* event_clone = base_event.clone();
	clones_arr.add(event_clone);
	event_container->insert(event_clone);
}
