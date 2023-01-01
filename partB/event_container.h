#ifndef EVENT_CONTAINER_H_
#define EVENT_CONTAINER_H_

#include "base_event.h"
#include "priority_linked_list.h"
#include "clones_array.h"

namespace mtm {
	class EventContainer {
	protected:
		class CompareEvents {
		public:
			int operator()(const BaseEvent* event1, const BaseEvent* event2) {
				if (*event1 > *event2) return NEGATIVE;
				else if (*event1 == *event2) return ZERO;
				else return POSITIVE;
			}
		};
		PriorityLinkedList<BaseEvent*, CompareEvents>* event_container;
		ClonesArray clones_arr;

	public:
		class EventIterator {
		private:
			Node<BaseEvent*>* node;
		public:
			EventIterator() : node(nullptr) {} 
			EventIterator(Node<BaseEvent*>* _node) : node(_node) {}
			EventIterator(const EventIterator& itr);
			~EventIterator() = default;

			EventIterator& operator=(const Node<BaseEvent*>& _node);
			EventIterator& operator++();
			BaseEvent& operator*();
			friend bool operator==(const EventIterator& itr1, const EventIterator& itr2) {
				
				if (itr1.node != nullptr && itr2.node == nullptr) {
					return false; 
				}
				if (itr1.node == nullptr) {
					return true;
				}
				return (*(itr1.node->element) == *(itr2.node->element));
				
			}
		};

		EventContainer();
		EventContainer(const EventContainer& container);
		virtual ~EventContainer();
		EventContainer& operator=(const EventContainer& container);
		virtual void add(const BaseEvent& base_event) = 0;

		EventIterator begin() const {
			if (event_container->getSize() == 0) {
				return EventIterator(nullptr);
			}
			return EventIterator(event_container->getFirstNode(*event_container));
		}

		EventIterator end() const {
			return EventIterator(nullptr);
		}
	};

	// for iterator
	bool operator!=(const EventContainer::EventIterator& itr1, const EventContainer::EventIterator& itr2);
}
#endif //EVENT_CONTAINER_H_
