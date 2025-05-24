#ifndef LEVEL_PRODUCER_H
#define LEVEL_PRODUCER_H

#include <nlohmann/json.hpp>
#include <fstream>
#include "Level.h"

class LevelProducer {
	nlohmann::json json_data;

	LevelProducer() {
		std::ifstream ifs("../assets/levels.json");
		if (!ifs) {
			throw std::runtime_error("Unable to open assets/levels.json");
		}
		ifs >> json_data;
		if (!json_data.contains("levels") || !json_data["levels"].is_object()) {
			throw std::runtime_error("Invalid JSON structure: missing 'levels' object");
		}
	}

public:
	static LevelProducer& instance() {
		static LevelProducer instance;
		return instance;
	}

	Level get_level(const std::string& name);
	[[nodiscard]] std::vector<std::string> list_levels() const;

	// Singleton access
	LevelProducer(const LevelProducer&) = delete;
	LevelProducer& operator=(const LevelProducer&) = delete;
	LevelProducer(LevelProducer&&) = delete;
	LevelProducer& operator=(LevelProducer&&) = delete;
};

#endif
