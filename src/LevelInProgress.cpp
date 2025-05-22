#include "LevelInProgress.h"
#include <iostream>

void LevelInProgress::calculate_physics(sf::Time dt)
{
	for (auto& plane : planes) {
		plane.follow_path(dt);
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

void LevelInProgress::add_move_point_to_selected_plane(sf::Vector2f approximate_destination, float radius)
{
	if (selected_plain == nullptr)
		return;
	sf::Vector3f plane_position = selected_plain->get_position();
	if (selected_plain->get_path().size() > 0)
		plane_position = selected_plain->get_path().back();

	std::optional<sf::Vector2f> result = airport.build_path(plane_position, approximate_destination, radius);
	if (result.has_value())
	{
		sf::Vector3f res = sf::Vector3f(result.value().x, result.value().y, 0);
		if (res != plane_position)
			selected_plain->add_point_to_path(sf::Vector3f(res.x, res.y, 0));
	}
}

void LevelInProgress::clear_path_for_selected_plane()
{
	if (selected_plain == nullptr)
		return;
	selected_plain->set_path({});
}
