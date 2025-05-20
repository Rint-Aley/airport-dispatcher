#include "Airport.h"
#include "float.h"
#include <SFML/System/Vector2.hpp>

Airport::Airport(const std::vector<Road>& roads, std::vector<Runway*> runways) : roads(roads), runways(runways)
{
}

void Airport::add_road(Road new_road)
{
	roads.push_back(new_road);
}

void Airport::add_runway(Runway* new_runway)
{
	runways.push_back(new_runway);
}

std::vector<sf::Vector3f> Airport::build_path(const sf::Vector3f& initial_position, const sf::Vector2f& approximate_destination)
{
	/*if (roads.size() == 0)
		return {};
	Road* destination_road = nullptr;
	sf::Vector2f destination;

	float closest_distance = FLT_MAX;
	for (auto road : roads) {
		sf::Vector2f begin = road.get_coordinates().first, end = road.get_coordinates().second;
		if ((begin - approximate_destination).length() < closest_distance) {
			destination = begin;
			destination_road = &road;
			closest_distance = (begin - approximate_destination).length();
		}
		else if ((end - approximate_destination).length() < closest_distance) {
			destination = end;
			destination_road = &road;
			closest_distance = (end - approximate_destination).length();
		}
	}*/
	return std::vector<sf::Vector3f>();
}


