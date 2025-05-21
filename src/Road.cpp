#include "Road.h"
#include <SFML/Graphics/ConvexShape.hpp>

Road::Road(const sf::Vector2f& a, const sf::Vector2f& b, float width, const std::vector<Road*>& adjacent_roads) :
	coordinates{ a, b }, width(width), adjacent_roads(adjacent_roads)
{
}

float Road::get_width() const
{
	return width;
}

std::pair<sf::Vector2f, sf::Vector2f> Road::get_coordinates() const
{
	return { coordinates[0], coordinates[1] };
}

void Road::add_adjacent_road(Road* adj_road)
{
	adjacent_roads.push_back(adj_road);
}

void Road::delete_adjacent_road(Road* adj_road)
{
	// adjacent_roads.erase(adjacent_roads.remove(adj_road));
}

void Road::draw(sf::RenderWindow& window) const
{
	sf::Vector2f direction = coordinates[1] - coordinates[0];
	direction = direction / direction.length();
	sf::Vector2f normal_vec(direction.y, -direction.x);
	normal_vec *= width / 2;
	sf::ConvexShape shape(4);
	shape.setFillColor(sf::Color::Green);
	shape.setPoint(0, coordinates[0] + normal_vec);
	shape.setPoint(1, coordinates[0] - normal_vec);
	shape.setPoint(2, coordinates[1] - normal_vec);
	shape.setPoint(3, coordinates[1] + normal_vec);
	window.draw(shape);
}

