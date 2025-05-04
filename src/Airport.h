#ifndef AIRPORT_H
#define AIRPORT_H

#include <vector>
#include <map>
#include "Road.h"
#include "Runway.h"

class Airport {
private:
	std::vector<Road> roads;
	std::vector<Runway*> runways;
	// std::map<size_t, > time to event
	// schedule: plane, what, when
public:

};

#endif