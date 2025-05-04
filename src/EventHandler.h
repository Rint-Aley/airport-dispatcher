#pragma once 

struct Event {
	enum {
		PlaneLaunch,
		PlaneLand,
		PlaneCrush,
	} event;
	void* additional_info;
};

class EventHandler {
	void virtual send_event(const Event& event) = delete;
};