#include "Plane.h"

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

void Plane::follow_path()
{
	if (path.size() == 1)
	{
		sf::Vector3f a = *path.begin(), b = *(path.begin()++);
		float braking_path = velocity.length() * velocity.length() / 2 / max_slowdown_accelertion;
		sf::Vector3f S = (b - position);
		// check if S = a*-direction
		if (S.length() <= braking_path)
		{
			acceleration = direction * -(velocity.length() * velocity.length() / 2 / S.length());
			velocity += acceleration;
			position += velocity;
		}
		else if (velocity.length() < max_velocity_on_the_ground)
		{
			// change acceleration???
			velocity += acceleration;
		}
		position += velocity;
	}
	if (path.size() >= 2)
	{
		sf::Vector3f a = *path.begin(), b = *(path.begin()++), c = *(path.begin()++++);
		sf::Vector3f S = (b - position);
		// check if S = a*-direction
	}
}

void Plane::launch()
{
	if (velocity.length() == 0) 
	{
		acceleration = direction * max_acceleration;
	}
	else if (velocity.length() >= launch_speed)
	{
		acceleration.z = 1;
	}
	velocity += acceleration;
	position += velocity;
}
