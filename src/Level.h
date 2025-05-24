#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Airport.h"
#include "Plane.h"

class Level {
protected:
	Airport airport;
	std::vector<Plane> planes;
	std::vector<Plane*> landing_list;
public:
	Level(Airport&& airport, std::vector<Plane>&& planes, std::vector<Plane*>&& landing_list) :
		airport(std::move(airport)), planes(std::move(planes)), landing_list(std::move(landing_list)) {}
};

#endif