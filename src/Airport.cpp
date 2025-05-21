#include "Airport.h"
#include "float.h"
#include <SFML/System/Vector2.hpp>

Airport::Airport(const std::vector<Road*>& roads, std::vector<Runway*> runways) : roads(roads), runways(runways)
{
}

Airport::~Airport()
{
	for (auto road : roads) {
		delete road;
	}
}

Airport::Airport(Airport&& other) noexcept
{
	roads = other.roads;
	runways = other.runways;
	schedule = other.schedule;
	other.roads.clear();
}

//void Airport::add_road(Road new_road)
//{
//	roads.push_back(new_road);
//}

void Airport::add_runway(Runway* new_runway)
{
	runways.push_back(new_runway);
}

//std::vector<sf::Vector3f> Airport::build_path(const sf::Vector3f& initial_position, const sf::Vector2f& approximate_destination)
//{
//	if (roads.size() == 0)
//		return {};
//	Road* destination_road = nullptr;
//	sf::Vector2f destination;
//
//	float closest_distance = FLT_MAX;
//	for (auto road : roads) {
//		sf::Vector2f begin = road.get_coordinates().first, end = road.get_coordinates().second;
//		if ((begin - approximate_destination).length() < closest_distance) {
//			destination = begin;
//			destination_road = &road;
//			closest_distance = (begin - approximate_destination).length();
//		}
//		else if ((end - approximate_destination).length() < closest_distance) {
//			destination = end;
//			destination_road = &road;
//			closest_distance = (end - approximate_destination).length();
//		}
//	}
//	// TODO: A* or smth else to build path
//	return std::vector<sf::Vector3f>();
//}

void Airport::draw(sf::RenderWindow& window) const
{
	for (auto&& road : roads)
	{
		road->draw(window);
	}
}


