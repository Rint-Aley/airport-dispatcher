#include "Plane.h"
#include <SFML/Graphics/RectangleShape.hpp>

Plane::Plane(std::string name, const sf::Vector3f& intial_position, float max_velocity_on_the_ground, float max_velocity,
	float max_acceleration_on_the_ground, float max_acceleration, float max_slowdown_acceleration, float launch_speed) :
	name(name), position(intial_position), max_velocity_on_the_ground(max_velocity_on_the_ground), max_velocity(max_velocity),
	max_acceleration_on_the_ground(max_acceleration_on_the_ground), max_acceleration(max_acceleration),
	max_slowdown_acceleration(max_slowdown_acceleration), launch_speed(launch_speed),
	velocity({ 0, 0, 0 }), acceleration({ 0, 0, 0 }), direction({ 1, 0, 0 }), order(Order::FollowingPath)
{

}

void Plane::set_max_acceleration(float new_acceleration) 
{
	if (new_acceleration < 0)
		throw std::exception();
	max_acceleration = new_acceleration;
	required_length_to_rise = launch_speed * launch_speed / 2 / max_acceleration;
}

void Plane::set_max_slowdown_accelertion(float new_acceleration)
{

}

void Plane::set_path(const std::list<sf::Vector3f>& path)
{
	this->path = path;
}

void Plane::follow_path(sf::Time dt)
{
	if (path.size() == 0)
		return;
	if ((*path.begin() - position).length() == 0)
	{
		path.pop_front();
		follow_path(dt);
		return;
	}
	float max_velocity, max_acceleration;
	if (order == Order::FollowingPath)
	{
		max_velocity = max_velocity_on_the_ground;
		max_acceleration = max_acceleration_on_the_ground;
	}
	else
	{
		max_velocity = this->max_velocity;
		max_acceleration = this->max_acceleration;
	}
	direction = (*path.begin() - position) / (*path.begin() - position).length();
	velocity = direction * velocity.length();
	if (path.size() == 1)
	{
		sf::Vector3f a = *path.begin();
		sf::Vector3f S = a - position;
		float braking_path = velocity.length() * velocity.length() / 2 / max_slowdown_acceleration;
		if (S.length() <= braking_path)
		{
			acceleration = direction * -(velocity.length() * velocity.length() / 2 / S.length());
			velocity += acceleration * dt.asSeconds();
		}
		else if (velocity.length() < max_velocity)
		{
			acceleration = direction * max_acceleration;
			velocity += acceleration * dt.asSeconds();
			if (velocity.length() >= max_velocity) {
				velocity = direction * max_velocity;
			}
		}
		position += velocity * dt.asSeconds();
		S = a - position;
		if (S.x * direction.x < 0 || S.y * direction.y < 0)
		{
			position = a;
			velocity = sf::Vector3f(0, 0, 0);
			acceleration = sf::Vector3f(0, 0, 0);
			path.pop_front();
		}
	}
	if (path.size() >= 2)
	{
		sf::Vector3f a = *path.begin(), b = *(++path.begin());
		if (velocity.length() < max_velocity)
		{
			acceleration = direction * max_acceleration;
			velocity += acceleration * dt.asSeconds();
			if (velocity.length() >= max_velocity)
			{
				velocity = direction * max_velocity;
			}
		}
		position += velocity * dt.asSeconds();
		sf::Vector3f S = a - position;
		while ((S.x * direction.x < 0 || S.y * direction.y < 0) && path.size() > 0)
		{
			path.pop_front();
			position = a;
			direction = (b - a) / (b - a).length();
			position += direction * S.length();
			if (path.size() == 1) {
				S = b - position;
				if (S.x * direction.x < 0 || S.y * direction.y < 0) {
					position = b;
					velocity = sf::Vector3f(0, 0, 0);
					acceleration = sf::Vector3f(0, 0, 0);
					path.pop_front();
				}					
				return;
			}
			a = *path.begin(), b = *(++path.begin());
			S = a - position;
		}
	}
}

void Plane::launch()
{
	if (velocity.length() <= launch_speed)
	{
		acceleration = direction * max_acceleration;
	}
	else if (velocity.length() >= launch_speed)
	{
		direction.z = 1;
		// normalize direciton
		acceleration = direction * max_acceleration;
	}
	// if (position.z >= some value)
	//		stop rising
	velocity += acceleration; // * dt
	position += velocity; // * dt
}

void Plane::land()
{
	sf::Vector3f a = *path.begin(), b = *(path.begin()++);

}

void Plane::draw(sf::RenderWindow& window, bool is_selected) const
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(sf::Vector2f(position.x, position.y));
	rectangle.setSize(sf::Vector2f(10, 10));
	if (is_selected)
		rectangle.setFillColor(sf::Color::Red);
	else
		rectangle.setFillColor(sf::Color::White);
	window.draw(rectangle);
}

