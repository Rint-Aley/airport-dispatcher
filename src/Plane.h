#ifndef PLANE_H
#define PLANE_H

#include <string>
#include <list>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Plane {
private:
	enum Order {
		FollowingPath,
		Flying,
		WaintingForLaunch,
		Launching,
		Landing,
	};
	std::string name;
	float required_length_to_rise, required_length_to_land;
	float max_velocity_on_the_ground, max_velocity, max_acceleration_on_the_ground, max_acceleration, max_slowdown_acceleration, launch_speed;
	//float target_velocity_value;
	sf::Vector3f velocity, acceleration, position;
	sf::Vector3f direction;
	std::list<sf::Vector3f> path;
	Order order;
public:
	Plane(std::string name, const sf::Vector3f& intial_position, float max_velocity_on_the_ground, float max_velocity, 
		float max_acceleration_on_the_ground, float max_acceleration, float max_slowdown_acceleration, float launch_speed);

	sf::Vector3f get_position() const { return position; }

	void set_max_acceleration(float new_acceleration);
	void set_max_slowdown_accelertion(float new_acceleration);
	void set_path(const std::list<sf::Vector3f>& path);

	void follow_path(sf::Time dt);
	void launch();
	void land();

	void draw(sf::RenderWindow& window, bool is_selected = false) const;
};
#endif
