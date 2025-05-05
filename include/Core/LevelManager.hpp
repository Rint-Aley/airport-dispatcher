#pragma once

#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

#include "EventQueue.hpp"
#include "IAirplane.hpp"
#include "Runway.hpp"
#include "TaxiwayManager.hpp"

namespace Core {

    class LevelManager {
    public:
        /// @throws std::runtime_error при открытии конфига
        LevelManager(EventQueue& eq, const std::string& levels_cfg_path);

        /// загружает уровень (впп, рулежки и записывает в event queue время посадки и взлета
        /// возможно стоит убрать отсюда функцию записи в event_queue
        /// @throws std::runtime_error на ошибку при чтении необходимых ключей конфига
        void load_level(int lvl);

        [[nodiscard]] std::vector<std::unique_ptr<IAirplane>>& get_planes() { return m_planes; }
        [[nodiscard]] std::vector<Runway>& get_runways() { return m_runways; }
        [[nodiscard]] TaxiwayManager& get_taxiways() { return m_taxiways; }

    private:
        EventQueue& m_eq;
        nlohmann::json m_cfg;

        std::vector<std::unique_ptr<IAirplane>> m_planes;
        std::vector<Runway> m_runways;
        TaxiwayManager m_taxiways;

        void load_runways(const nlohmann::json& lvl_node);
        void load_taxiways(const nlohmann::json& lvl_node);
        void schedule_planes(const nlohmann::json& lvl_node);
    };

}