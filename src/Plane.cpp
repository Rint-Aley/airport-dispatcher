#include "Plane.h"
#include <SFML/Graphics/RectangleShape.hpp>

Plane::Plane(std::string name, const sf::Vector3f& intial_position, float max_velocity_on_the_ground, float max_velocity,
	float max_acceleration_on_the_ground, float max_acceleration, float max_slowdown_acceleration, float launch_speed) :
	name(name), position(intial_position), max_velocity_on_the_ground(max_velocity_on_the_ground), max_velocity(max_velocity),
	max_acceleration_on_the_ground(max_acceleration_on_the_ground), max_acceleration(max_acceleration),
	max_slowdown_acceleration(max_slowdown_acceleration), launch_speed(launch_speed),
	velocity({ 0, 0, 0 }), acceleration({ 0, 0, 0 }), direction({ 1, 0, 0 }), max_height(100)
{
	order = position.z > 0 ? Flying : OnTheGround;
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

void Plane::add_point_to_path(sf::Vector3f point)
{
	path.push_back(point);
}

void Plane::clear_path()
{
	path.clear();
}

void Plane::calculate_physics(sf::Time dt)
{
	switch (order) {
	case OnTheGround:
		follow_path(dt);
		break;
	case Flying:
		follow_path(dt);
		break;
	case Launching:
		launch(dt);
		break;
	case Landing:
		// land(dt);
		break;
	}
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
	if (order == Order::OnTheGround)
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

void Plane::prepare_to_launch(const Runway& runway)
{
	if (order != OnTheGround)
		return;

	sf::Vector2f position_2d = sf::Vector2f(position.x, position.y);
	sf::Vector2f runway_direction = runway.get_direciton();

	if (position_2d == runway.get_coordinates().first)
	{
		direction = sf::Vector3f(runway_direction.x, runway_direction.y, 0);
		order = Launching;
	}
	else if (position_2d == runway.get_coordinates().second)
	{
		runway_direction *= -1.0f;
		direction = sf::Vector3f(runway_direction.x, runway_direction.y, 0);
		order = Launching;
	}
}

void Plane::launch(sf::Time dt)
{
	if (velocity.length() <= launch_speed)
	{
		acceleration = direction * max_acceleration;
	}
	else if (velocity.length() >= launch_speed)
	{
		order = Flying;
		path.push_back(position + velocity * 10.0f + sf::Vector3f(0, 0, max_height));
		return;
	}
	velocity += acceleration * dt.asSeconds();
	position += velocity * dt.asSeconds();
}

void Plane::land(sf::Time dt)
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

