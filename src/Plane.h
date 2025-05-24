#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <list>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Runway.h"
#include "Event.h"
#include "Octagon.h"

class Plane {
public:
	enum Order {
		OnTheGround,
		Flying,
		WaintingForLaunch,
		Launching,
		Landing,
		WaitingForAcceptingRequest,
	};
private:
	std::string name;
	float required_length_to_rise, required_length_to_land, max_height;
	float max_velocity_on_the_ground, max_velocity, max_acceleration_on_the_ground, max_acceleration, max_slowdown_acceleration, launch_speed;
	sf::Vector3f velocity, acceleration, position, direction;
	std::list<sf::Vector3f> path;
	Order order;
	IEventReceiver* event_receiver;
	Runway* landing_runway;
	std::vector<OctagonPoint> circle;
	float cycles_befor_drop;
public:
	Plane(std::string name, const sf::Vector3f& intial_position, float max_velocity_on_the_ground, float max_velocity, 
		float max_acceleration_on_the_ground, float max_acceleration, float max_slowdown_acceleration, float launch_speed, float cycles_befor_drop);

	sf::Vector3f get_position() const { return position; }
	const std::list<sf::Vector3f>& get_path() { return path; }
	Order get_order() const { return order; }
	const std::string& get_name() const { return name; }
	float get_cycles_befor_drop() const { return cycles_befor_drop; }

	void set_max_acceleration(float new_acceleration);
	void set_max_slowdown_acceleration(float new_acceleration);
	void set_path(const std::list<sf::Vector3f>& path);
	void add_point_to_path(sf::Vector3f point);
	void clear_path();
	void set_event_receiver(IEventReceiver* event_receiver);
	void set_landing_runway(Runway* runway);
	void generate_circle(sf::Vector2f center);

	void calculate_physics(sf::Time dt);
	void follow_path(sf::Time dt);
	void prepare_to_launch(const Runway& runway);
	void launch(sf::Time dt);
	void land(sf::Time dt);
	void wait_for_request(sf::Time dt);

	void draw(sf::RenderWindow& window, bool is_selected = false) const;
};
#endif
