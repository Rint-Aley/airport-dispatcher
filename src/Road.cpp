#include "Road.h"

Road::Road(const sf::Vector2f& a, const sf::Vector2f b, float width, std::vector<Road*> adjacent_roads) :
	coordinates{ a, b }, width(width), adjacent_roads(adjacent_roads)
{
}

float Road::get_width()
{
	return width;
}

std::pair<sf::Vector2f, sf::Vector2f> Road::get_coordinates()
{
	return { coordinates[0], coordinates[1] };
}

void Road::add_adjacent_road(Road* adj_road)
{
	adjacent_roads.push_back(adj_road);
}

void Road::delete_adjacent_road(Road* adj_road)
{
	//adjacent_roads.erase(add_adjacent_road.remove(adj_road));
}

