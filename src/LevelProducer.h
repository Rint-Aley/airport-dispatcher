#ifndef LEVEL_PRODUCER_H
#define LEVEL_PRODUCER_H

#include <vector>
#include "Level.h"

namespace LevelProducer {
	Level Level1() {
		std::vector<Road*> roads;
		roads.push_back(new Runway({ 100, 100 }, { 100, 1000 }, 50, {}));
		roads.push_back(new Runway({ 500, 100 }, { 500, 1000 }, 50, {}));
		roads.push_back(new Road({ 100, 100 }, { 500, 100 }, 40, { &roads[0], &roads[1] }));
		roads.push_back(new Road({ 100, 1000 }, { 500, 1000 }, 40, { &roads[0], &roads[1]}));
		roads[0]->add_adjacent_road(roads[2]);
		roads[0]->add_adjacent_road(roads[3]);
		roads[1]->add_adjacent_road(roads[2]);
		roads[1]->add_adjacent_road(roads[3]);

		std::vector<Plane> planes;
		planes.push_back(Plane("plane 1", { 100, 100, 0 }, 100, 300, 20, 50, 15, 200));
		planes.push_back(Plane("plane 2", { 500, 100, 0 }, 100, 300, 20, 50, 15, 200));
		return Level(Airport(roads, { (Runway*)roads[0], (Runway*)roads[1] }, {Airport::TakeoffInfo(0.0f, &planes[0])}), std::move(planes));
	}
}

#endif
