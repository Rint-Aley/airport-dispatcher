#include "Runway.h"
#include <SFML/Graphics/ConvexShape.hpp>

Runway::Runway(const sf::Vector2f& a, const sf::Vector2f& b, float width, std::vector<Road*> adjacent_roads) :
	Road(a, b, width, adjacent_roads)
{
}

void Runway::draw(sf::RenderWindow& window) const
{
	auto coordinates = get_coordinates();
	sf::Vector2f direction = coordinates.first - coordinates.second;
	direction = direction / direction.length();
	sf::Vector2f normal_vec(direction.y, -direction.x);
	normal_vec *= get_width() / 2;
	sf::ConvexShape shape(4);
	shape.setFillColor(sf::Color::Cyan);
	shape.setPoint(0, coordinates.first + normal_vec);
	shape.setPoint(1, coordinates.first - normal_vec);
	shape.setPoint(2, coordinates.second - normal_vec);
	shape.setPoint(3, coordinates.second + normal_vec);
	window.draw(shape);
}
