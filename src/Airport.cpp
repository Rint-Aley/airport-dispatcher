#include "Airport.h"
#include "float.h"
#include <SFML/System/Vector2.hpp>

Airport::Airport(const std::vector<Road*>& roads, std::vector<Runway*> runways) : roads(roads), runways(runways)
{
}

Airport::~Airport()
{
	for (auto road : roads)
	{
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

void Airport::add_road(Road* new_road)
{
	roads.push_back(new_road);
}

void Airport::add_runway(Runway* new_runway)
{
	runways.push_back(new_runway);
}

std::optional<sf::Vector2f> Airport::build_path(const sf::Vector3f& initial_position, const sf::Vector2f& approximate_destination, float radius)
{
	sf::Vector2f destination;
	bool node_was_found = false;
	float closest_distance = radius;

	for (auto road : roads)
	{
		auto [begin, end] = road->get_coordinates();
		if ((begin - approximate_destination).length() < closest_distance)
		{
			node_was_found = true;
			destination = begin;
			closest_distance = (begin - approximate_destination).length();
		}
		else if ((end - approximate_destination).length() < closest_distance)
		{
			node_was_found = true;
			destination = end;
			closest_distance = (end - approximate_destination).length();
		}
	}
	if (!node_was_found)
		return std::nullopt;

	std::vector<Road*> destination_roads;
	for (auto road : roads)
	{
		auto [a, b] = road->get_coordinates();
		if (a == destination || b == destination) 
			destination_roads.push_back(road);
	}

	for (auto destination_road : destination_roads)
		if (destination_road->is_on_the_road(sf::Vector2f(initial_position.x, initial_position.y)))
			return destination;
	return std::nullopt;
}

void Airport::draw(sf::RenderWindow& window) const
{
	for (auto&& road : roads)
	{
		road->draw(window);
	}
}


