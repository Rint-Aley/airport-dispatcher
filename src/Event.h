#ifndef EVENT_H
#define EVENT_H

#include "Plane.h"

struct Event {
	enum {
		PlaneLaunch,
		PlaneLand,
		PlaneCrush,
	} event;
	Plane plane;
	void* additional_info;
};

#endif
