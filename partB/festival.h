#ifndef FESTIVAL_H_
#define FESTIVAL_H_

#include "event_container.h"

namespace mtm {
	class Festival : public EventContainer {
	private:
		DateWrap date;
	public:
		Festival(const DateWrap& _date);
		Festival(const Festival& festival);
		~Festival() = default;
		Festival& operator=(const Festival& festival);
		void add(const BaseEvent& base_event) override;
	};
}
#endif //FESTIVAL_H_
