#include "LevelInProgress.h"
#include <iostream>

LevelInProgress::LevelInProgress(Level&& base_level)
	: Level((Level&&)base_level), time(0), penalty(0), selected_plain(nullptr), runway_selection_mode(false), event_queue()
{
	for (auto& plane : planes)
	{
		plane.set_event_receiver(this);
		if (plane.get_position().z > 0)
		{
			plane.generate_circle(airport.get_center());
		}
	}
}

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
	for (size_t i = 0; i < planes.size(); ++i) 
	{
		for (size_t j = i + 1; j < planes.size(); ++j)
		{
			if ((planes[i].get_position() - planes[j].get_position()).length() < 30) // number is the sum of collision models
			{
				send_event(Event(Event::Type::PlaneCrush, &planes[i]));
			}
		}
	}
}

void LevelInProgress::handle_events()
{
	while (!event_queue.empty())
	{
		const Event& event = event_queue.front();
		if (event.type == Event::Type::PlaneLaunch)
		{
			std::cout << "Plane " << event.plane->get_name() << " has been launched\n";
			if (selected_plain == event.plane)
				selected_plain = nullptr;
		}
		else if (event.type == Event::Type::PlaneCrush)
		{
			std::cout << "Plane " << event.plane->get_name() << " has been crushed. Game over!\n";
		}
		event_queue.pop();
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

bool LevelInProgress::assign_runway(sf::Vector2f approximate_destination, float radius, Plane* plane)
{
	auto a = airport.find_runway(approximate_destination, radius);
	plane->set_landing_runway(a);
	return a != nullptr;
}

void LevelInProgress::send_event(const Event& event)
{
	event_queue.push(event);
}
