#ifndef AIRPORT_H
#define AIRPORT_H

#include <vector>
#include <map>
#include "Road.h"
#include "Runway.h"
#include "Event.h"

class Airport {
private:
	std::vector<Road*> roads;
	std::vector<Runway*> runways;
	std::map<size_t, Event> schedule;
public:
	Airport(const std::vector<Road*>& roads, std::vector<Runway*> runways);
	Airport(Airport& other) = delete;
	Airport(Airport&& other) noexcept;
	~Airport();

	//const std::vector<Road>& get_roads() const { return roads; }
	const std::vector<Runway*>& get_runways() const { return runways; }

	void add_road(Road new_road);
	void add_runway(Runway* new_runway);

	std::vector<sf::Vector3f> build_path(const sf::Vector3f& initial_position, const sf::Vector2f& approximate_destination);

	void draw(sf::RenderWindow& window) const;
};

#endif