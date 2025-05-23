#ifndef LEVEL_IN_PROGRESS_H
#define LEVEL_IN_PROGRESS_H

#include "Level.h"
#include "Plane.h"

class LevelInProgress : public Level {
private:
	float penalty, time;
	Plane* selected_plain;
	bool runway_selection_mode;
public:
	LevelInProgress(Level&& base_level) : Level((Level&&)base_level), time(0), penalty(0), selected_plain(nullptr), runway_selection_mode(false) {}

	void toggle_runway_selection_mode();

	void calculate_physics(sf::Time dt);
	void check_collisions();
	void handle_events();
	void draw(sf::RenderWindow& window) const;

	void select_closest_plain_in_radius(sf::Vector2f position, float radius);
	void add_move_point_to_selected_plane(sf::Vector2f approximate_destination, float radius);
	void clear_path_for_selected_plane();
};

#endif