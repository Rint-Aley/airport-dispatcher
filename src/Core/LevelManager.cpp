#include "Core/LevelManager.hpp"
#include <fstream>
#include <stdexcept>
#include <Core/AirplaneFactory.hpp>

using namespace Core;

LevelManager::LevelManager(EventQueue& eq, const std::string& levels_cfg_path) : m_eq(eq) {
    std::ifstream in(levels_cfg_path);
    if (!in) throw std::runtime_error("Cannot open config: " + levels_cfg_path);
    in >> m_cfg;
}

void LevelManager::load_level(const int lvl) {
    auto levels = m_cfg.at("levels");
    const std::string key = std::to_string(lvl);
    if (!levels.contains(key))
        throw std::runtime_error("Level not found: " + key);

    const auto& node = levels.at(key);

    load_runways(node);
    load_taxiways(node);
    schedule_planes(node);
}

void LevelManager::load_runways(const nlohmann::json& lvl_node) {
    m_runways.clear();
    for (auto& r : lvl_node.at("runways")) {
        Runway rw;
        rw.id = r.at("id").get<int>();
        rw.length = r.at("length").get<int>();
        rw.busy = false;
        m_runways.push_back(rw);
    }
}

void LevelManager::load_taxiways(const nlohmann::json& lvl_node) {
    m_taxiways = TaxiwayManager::from_json(lvl_node.at("taxiways"));
}

void LevelManager::schedule_planes(const nlohmann::json& lvl_node) {
    m_planes.clear();

    const float arrival_dt = static_cast<float>(lvl_node.value("arrival_interval", 2.0));
    const float departure_dt = static_cast<float>(lvl_node.value("departure_interval", 3.0));

    const auto& arr = lvl_node.at("arrivals");
    for (size_t i = 0; i < arr.size(); ++i) {
        auto type = arr[i].get<std::string>();
        const int id = static_cast<int>(i + 1);
        m_planes.push_back(AirplaneFactory::create(type, id, FlightRole::Arrival));
        auto* raw = m_planes.back().get();
        m_eq.schedule(static_cast<float>(i) * arrival_dt, [raw] {
            raw->set_state(FlightState::QueuedForLanding);
        });
    }

    const auto& dep = lvl_node.at("departures");
    const size_t offs = arr.size();
    for (size_t i = 0; i < dep.size(); ++i) {
        auto type = dep[i].get<std::string>();
        const int id = static_cast<int>(offs + i + 1);
        m_planes.push_back(AirplaneFactory::create(type, id, FlightRole::Departure));
        auto* raw = m_planes.back().get();
        m_eq.schedule(static_cast<float>(i) * departure_dt + 1.f, [raw] {
            raw->set_state(FlightState::QueuedForTakeoff);
        });
    }
}
