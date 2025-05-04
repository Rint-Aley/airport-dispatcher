#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include "SFML/System/Vector2.hpp"

class Road {
private:
	sf::Vector2f coordinates[2];
	float width;
	std::vector<Road*> adjacent_roads;
public:
	Road(const sf::Vector2f& a, const sf::Vector2f b,
		float width, std::vector<Road*> adjacent_roads);

	const std::vector<Road*> get_adjacent_roads() { return adjacent_roads; }
	float get_width();
	std::pair<sf::Vector2f, sf::Vector2f> get_coordinates();

	void add_adjacent_road(Road* adj_road);
	void delete_adjacent_road(Road* adj_road);
};
#endif
