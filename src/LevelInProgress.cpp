#include "LevelInProgress.h"

void LevelInProgress::calculate_physics(sf::Time dt)
{
	for (auto plane : planes) {
		// call method in plane
	}
}

void LevelInProgress::draw(sf::RenderWindow& window) const
{
	airport.draw(window);
	for (auto& plane : planes) {
		plane.draw(window, &plane == selected_plain);
	}
}

void LevelInProgress::select_closest_plain_in_radius(sf::Vector2f position, float radius)
{
	sf::Vector3f pos(position.x, position.y, 0);
	Plane* result = nullptr;
	for (auto& plane : planes) {
		// check for its order
		if ((plane.get_position() - pos).length() < radius) {
			result = &plane;
			radius = (plane.get_position() - pos).length();
		}
	}
	selected_plain = result;
}
