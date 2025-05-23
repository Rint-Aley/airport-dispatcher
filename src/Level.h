#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "Airport.h"
#include "Plane.h"

class Level {
protected:
	Airport airport;
	std::vector<Plane> planes;
public:
	Level(Airport&& airport, std::vector<Plane>&& planes) : airport(std::move(airport)), planes(std::move(planes)) {}

	const std::vector<Plane>& get_planes() const;

	void add_plane();
	
};

#endif