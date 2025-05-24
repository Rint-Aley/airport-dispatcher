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
		roads.push_back(new Runway({ 250, 100 }, { 250, 1000 }, 50, { &roads[2], &roads[3] }));
		roads[2]->add_adjacent_road(roads[4]);
		roads[3]->add_adjacent_road(roads[4]);


		std::vector<Plane> planes;
		planes.push_back(Plane("plane 1", { 100, 100, 0 }, 100, 300, 30, 70, 50, 200, 0));
		planes.push_back(Plane("plane 2", { 500, 100, 0 }, 100, 300, 20, 50, 50, 200, 0));
		planes.push_back(Plane("plane 3", { 500, 100, 500 }, 100, 500, 200, 500, 100, 300, 2));
		planes.push_back(Plane("plane 4", { 1000, 700, 500 }, 200, 800, 100, 600, 100, 300, 2));
		return Level(Airport(roads, { (Runway*)roads[0], (Runway*)roads[1], (Runway*)roads[4] }, { Airport::TakeoffInfo(10.0f, &planes[0]), Airport::TakeoffInfo(10.0f, &planes[1]) },
			{ 250, 500 }), std::move(planes), {&planes[2], &planes[3]});
	}
}

#endif
