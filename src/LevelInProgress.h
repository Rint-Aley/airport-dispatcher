#ifndef LEVEL_IN_PROGRESS_H
#define LEVEL_IN_PROGRESS_H

#include "Level.h"

class LevelInProgress : public Level {
private:
	float penalty, time;
public:
	LevelInProgress() : time(0), penalty(0) {}

	void calculate_physics(sf::Time dt);
	void check_collisions();
	void handle_events();
};

#endif