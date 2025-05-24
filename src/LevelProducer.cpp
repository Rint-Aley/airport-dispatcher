#include "LevelProducer.h"

Level LevelProducer::get_level(const std::string &name) {
    const auto& levels_obj = json_data["levels"];
    if (!levels_obj.contains(name)) {
        throw std::out_of_range("Level name '" + name + "' not found in JSON");
    }
    const auto& jlvl = levels_obj[name];

    std::vector<Road*> roads;
    std::vector<Runway*> runways;
    std::unordered_map<std::string, Road*> road_map;

    for (const auto& item : jlvl["roads"]) {
        std::string id = item.value("id", "");
        sf::Vector2f start(item["start"][0], item["start"][1]);
        sf::Vector2f end(item["end"][0], item["end"][1]);
        const float width = item["width"];
        std::string type = item.value("type", "road");
        Road* road_ptr = nullptr;
        if (type == "runway") {
            auto* rw = new Runway(start, end, width, {});
            runways.push_back(rw);
            road_ptr = rw;
        } else {
            road_ptr = new Road(start, end, width, {});
        }
        roads.push_back(road_ptr);
        if (!id.empty()) {
            road_map[id] = road_ptr;
        }
    }

    for (const auto& item : jlvl["roads"]) {
        std::string id = item.value("id", "");
        if (id.empty()) continue;
        Road* src = road_map[id];
        for (const auto& adj_id : item.value("adjacent_ids", std::vector<std::string>{})) {
            auto it = road_map.find(adj_id);
            if (it != road_map.end()) {
                src->add_adjacent_road(it->second);
            }
        }
    }

    std::vector<Plane> planes;
    for (const auto& item : jlvl["planes"]) {
        std::string pname = item["name"];
        const auto& pos = item["position"];
        planes.emplace_back(
            pname,
            sf::Vector3f(pos[0], pos[1], pos[2]),
            item["max_velocity_on_ground"],
            item["max_velocity"],
            item["max_acceleration_on_ground"],
            item["max_acceleration"],
            item["max_slowdown_acceleration"],
            item["launch_speed"]
        );
    }

    return { Airport(roads, runways), planes };
}

std::vector<std::string> LevelProducer::list_levels() const {
    std::vector<std::string> names;
    const auto& levels_obj = json_data["levels"];
    for (auto it = levels_obj.begin(); it != levels_obj.end(); ++it) {
        names.push_back(it.key());
    }
    return names;
}

std::pair<size_t, size_t> LevelProducer::get_level_info(const std::string &name) {
    const auto& levels_obj = json_data["levels"];
    if (!levels_obj.contains(name)) {
        throw std::out_of_range("Level name '" + name + "' not found in JSON");
    }
    const auto& jlvl = levels_obj[name];
    return {jlvl["roads"].size(), jlvl["planes"].size()};
}
