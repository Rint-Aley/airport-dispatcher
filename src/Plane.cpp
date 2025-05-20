#include "Plane.h"
#include <SFML/Graphics/RectangleShape.hpp>

Plane::Plane() : name(), velocity{ 0, 0, 0 }, acceleration{ 0, 0, 0 }, position{ 0, 0, 0 }, path(), direction{ 0, 0, 0 }, max_velocity_on_the_ground(300), max_acceleration_on_the_ground(30), max_slowdown_accelertion(100)
{

}

sf::Vector3f Plane::get_position()
{
	return position;
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

void Plane::follow_path_on_the_ground(sf::Time dt)
{
	if (path.size() == 0)
		return;
	if ((*path.begin() - position).length() == 0) {
		path.pop_front();
		follow_path_on_the_ground(dt);
		return;
	}
	direction = (*path.begin() - position) / (*path.begin() - position).length();
	velocity = direction * velocity.length();
	if (path.size() == 1)
	{
		sf::Vector3f a = *path.begin();
		sf::Vector3f S = a - position;
		float braking_path = velocity.length() * velocity.length() / 2 / max_slowdown_accelertion;
		if (S.length() <= braking_path)
		{
			acceleration = direction * -(velocity.length() * velocity.length() / 2 / S.length());
			velocity += acceleration * dt.asSeconds();
		}
		else if (velocity.length() < max_velocity_on_the_ground)
		{
			acceleration = direction * max_acceleration_on_the_ground;
			velocity += acceleration * dt.asSeconds();
			if (velocity.length() >= max_velocity_on_the_ground) { 
				velocity = direction * max_velocity_on_the_ground;
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
		if (velocity.length() < max_velocity_on_the_ground)
		{
			acceleration = direction * max_acceleration_on_the_ground;
			velocity += acceleration * dt.asSeconds();
			if (velocity.length() >= max_velocity_on_the_ground)
			{
				velocity = direction * max_velocity_on_the_ground;
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

void Plane::follow_path_in_the_sky()
{
	sf::Vector3f a = *path.begin();
	sf::Vector3f S = (a - position);
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

void Plane::draw(sf::RenderWindow& window)
{
	sf::RectangleShape rectangle;
	rectangle.setPosition(sf::Vector2f(position.x, position.y));
	//rectangle.setPosition(sf::Vector2f(100, 100));
	rectangle.setSize(sf::Vector2f(10, 10));
	rectangle.setFillColor(sf::Color::Red);
	window.draw(rectangle);
}

