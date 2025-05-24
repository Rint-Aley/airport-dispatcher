#ifndef AIRPORT_H
#define AIRPORT_H

#include <vector>
#include <map>
#include "Road.h"
#include "Runway.h"
#include "Event.h"

class Airport {
public:
	struct TakeoffInfo {
		float time;
		Plane* plane;
		Runway* runway;
		TakeoffInfo(float time, Plane* plane) : plane(plane), time(time), runway(nullptr) {}
	};
private:
	std::vector<Road*> roads;
	std::vector<Runway*> runways;
	std::vector<TakeoffInfo> take_off_list;
	sf::Vector2f center;

public:
	Airport(const std::vector<Road*>& roads, const std::vector<Runway*>& runways, const std::vector<TakeoffInfo>& schedule, sf::Vector2f center);
	Airport(Airport& other) = delete;
	Airport(Airport&& other) noexcept;
	~Airport();

	const std::vector<Road*>& get_roads() const { return roads; }
	const std::vector<Runway*>& get_runways() const { return runways; }
	sf::Vector2f get_center() const { return center; }

	void add_road(Road* new_road);
	void add_runway(Runway* new_runway);

	void add_plane_to_takeoff_list(Plane* plane, Runway* runway);
	void delete_plane_from_takeoff_list(Plane* plane);

	// Returns the closest to cursor node that is accessible from the current position
	std::optional<sf::Vector2f> build_path(const sf::Vector3f& initial_position, const sf::Vector2f& approximate_destination, float radius);
	Runway* find_runway(sf::Vector2f coordinates);
	Runway* find_runway(sf::Vector2f coordinates, float radius);
	float measure_delay(const Plane& plane, float current_time);
	void launch_planes(float current_time);

	void draw(sf::RenderWindow& window) const;
};

#endif