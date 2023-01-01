#include "event_container.h"

using mtm::BaseEvent;
using mtm::EventContainer;
using mtm::PriorityLinkedList;
using mtm::ClonesArray;
using mtm::Node;

EventContainer::EventContainer() :
	event_container(new PriorityLinkedList<BaseEvent*, CompareEvents>(CompareEvents())), clones_arr() {}

EventContainer::EventContainer(const EventContainer& container) : 
	event_container(new PriorityLinkedList<BaseEvent*, CompareEvents>(*(container.event_container))) {}


EventContainer::~EventContainer()
{
	for (int i = 0; i < clones_arr.counter; i++) {
		delete clones_arr.clone_ptr[i];
	}

	delete event_container;
}

EventContainer& EventContainer::operator=(const EventContainer& container)
{
	if (this == &container) {
		return *this;
	}
	delete event_container;
	event_container = container.event_container;
	return *this;
}


mtm::EventContainer::EventIterator::EventIterator(const EventIterator& itr) : node((itr.node)) {}

EventContainer::EventIterator& EventContainer::EventIterator::operator=(const Node<BaseEvent*>& _node)
{
	if (node == &_node) {
		return *this;
	}
	delete node;
	*node = _node;
	return *this;
}

EventContainer::EventIterator& EventContainer::EventIterator::operator++()
{
	node = node->next;
	if (node == nullptr) {
		return *this;
	}
	return *this;
}

BaseEvent& EventContainer::EventIterator::operator*()
{
	return **(node->element);
}

bool mtm::operator!=(const EventContainer::EventIterator& itr1, const EventContainer::EventIterator& itr2)
{
	return (!(itr1 == itr2));
}
