#ifndef LEVEL_IN_PROGRESS_H
#define LEVEL_IN_PROGRESS_H

#include "Level.h"
#include "Plane.h"
#include "Event.h"
#include "Airport.h"
#include <queue>

class LevelInProgress : public Level, public IEventReceiver {
private:
	float penalty, time;
	Plane* selected_plain;
	bool runway_selection_mode;
	std::queue<Event> event_queue;
public:
	LevelInProgress(Level&& base_level);

	const std::vector<Plane*>& get_landing_list() const { return landing_list; }

	void toggle_runway_selection_mode();

	void calculate_physics(sf::Time dt);
	void check_collisions();
	void handle_events();
	void draw(sf::RenderWindow& window) const;

	void select_closest_plain_in_radius(sf::Vector2f position, float radius);
	void add_move_point_to_selected_plane(sf::Vector2f approximate_destination, float radius);
	void clear_path_for_selected_plane();
	bool assign_runway(sf::Vector2f approximate_destination, float radius, Plane* plane);

	void send_event(const Event& event) override;
};

#endif