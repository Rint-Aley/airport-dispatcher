#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Airport.h"
#include "Plane.h"

class Level {
private:
	std::vector<Airport> airports;
	std::vector<Plane> planes;
};

#endif