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
	float max_velocity_on_the_ground, max_acceleration_on_the_ground, max_acceleration, max_slowdown_accelertion, launch_speed;
	float target_velocity_value;
	sf::Vector3f velocity, acceleration, position;
	sf::Vector3f direction;
	std::list<sf::Vector3f> path;
	Order order;
public:
	explicit Plane();

	sf::Vector3f get_position();

	void set_max_acceleration(float new_acceleration);
	void set_max_slowdown_accelertion(float new_acceleration);
	void set_path(const std::list<sf::Vector3f>& path);

	void follow_path_on_the_ground(sf::Time dt);
	void follow_path_in_the_sky();
	void launch();
	void land();

	void draw(sf::RenderWindow& window);
};
#endif
