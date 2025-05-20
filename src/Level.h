#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Airport.h"
#include "Plane.h"

class Level {
protected:
	std::vector<Airport> airports;
	std::vector<Plane> planes;
public:
	Level();

	const std::vector<Plane>& get_planes() const;
	const std::vector<Airport>& get_airports() const;

	void add_plane();
	
};

#endif