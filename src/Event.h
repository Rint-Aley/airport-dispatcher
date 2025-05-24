#ifndef EVENT_H
#define EVENT_H

class Plane;

struct Event {
	enum Type {
		PlaneLaunch,
		PlaneCrush,
		BuildPath,
	} type;
	Plane* plane;

	Event(Event::Type type, Plane* plane) : type(type), plane(plane) {}
};

class IEventReceiver{
public:
	virtual void send_event(const Event& event) = 0;
};

#include "Plane.h"

#endif
