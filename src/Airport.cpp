#include "Airport.h"
#include "float.h"
#include <SFML/System/Vector2.hpp>

Airport::Airport(const std::vector<Road*>& roads, const std::vector<Runway*>& runways, const std::vector<TakeoffInfo>& schedule) 
	: roads(roads), runways(runways), take_off_list(schedule) {}

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
	take_off_list = other.take_off_list;
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

void Airport::add_plane_to_takeoff_list(Plane* plane, Runway* runway)
{
	for (auto& takeoff_info : take_off_list)
		if (takeoff_info.plane == plane)
			takeoff_info.runway = runway;
}

void Airport::delete_plane_from_takeoff_list(Plane* plane)
{
	for (auto& takeoff_info : take_off_list)
		if (takeoff_info.plane == plane)
			takeoff_info.runway = nullptr;
}

void Airport::change_runway_for_plane(const Plane& plane, Runway* runway)
{
	for (auto& landing_info : landing_list)
		if (landing_info.plane == &plane)
			landing_info.runway = runway;
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

Runway* Airport::find_runway(sf::Vector2f coordinates)
{
	for (auto runway : runways) 
		if (runway->get_coordinates().first == coordinates || runway->get_coordinates().second == coordinates)
			return runway;
	return nullptr;
}

float Airport::measure_delay(const Plane& plane, float current_time)
{
	for (auto& node : take_off_list)
	{
		if (node.plane == &plane)
		{
			return current_time - node.time;
		}
	}
	return 0.0f;
}

void Airport::launch_planes(float current_time)
{
	for (auto& take_off_info : take_off_list)
	{
		if (take_off_info.time <= current_time && take_off_info.runway != nullptr)
		{
			take_off_info.plane->prepare_to_launch(*take_off_info.runway);				
		}
	}
}

void Airport::draw(sf::RenderWindow& window) const
{
	for (auto&& road : roads)
	{
		road->draw(window);
	}
}
