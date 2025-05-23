#include "LevelInProgress.h"
#include <iostream>

void LevelInProgress::toggle_runway_selection_mode()
{
	runway_selection_mode = !runway_selection_mode;
}

void LevelInProgress::calculate_physics(sf::Time dt)
{
	time += dt.asSeconds();
	airport.launch_planes(time);
	for (auto& plane : planes) {
		plane.calculate_physics(dt);
	}
}

void LevelInProgress::check_collisions()
{
}

void LevelInProgress::handle_events()
{
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
		if ((plane.get_position() - pos).length() < radius && plane.get_order() == Plane::OnTheGround) {
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
		airport.delete_plane_from_takeoff_list(selected_plain);
		if (runway_selection_mode) 
		{
			Runway* runway = airport.find_runway(result.value());
			airport.add_plane_to_takeoff_list(selected_plain, runway);
			toggle_runway_selection_mode();
		}
		sf::Vector3f res = sf::Vector3f(result.value().x, result.value().y, 0);
		if (res != plane_position)
			selected_plain->add_point_to_path(sf::Vector3f(res.x, res.y, 0));
	}
}

void LevelInProgress::clear_path_for_selected_plane()
{
	if (runway_selection_mode)
		toggle_runway_selection_mode();
	if (selected_plain == nullptr)
		return;
	selected_plain->set_path({});
}
