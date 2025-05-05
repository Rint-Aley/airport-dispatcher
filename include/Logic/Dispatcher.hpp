#pragma once

#include <vector>
#include <optional>

#include <Core/Runway.hpp>
#include <Core/TaxiwayManager.hpp>
#include <Core/EventQueue.hpp>
#include <Core/IAirplane.hpp>
#include "PenaltyManager.hpp"

namespace Logic {

    class Dispatcher {
    public:
        Dispatcher(std::vector<Core::Runway>& runways, Core::TaxiwayManager& taxiways,
            Core::EventQueue& eq, PenaltyManager& penalty_mgr);

        void set_time(const float now) { m_current_time = now; }

        void process_landing(Core::IAirplane* plane);
        void process_takeoff(Core::IAirplane* plane);

    private:
        /// ближайший к началу массива m_runways
        [[nodiscard]] std::optional<size_t> find_available_runway(int req_len) const;

        std::vector<Core::Runway>& m_runways;
        Core::TaxiwayManager& m_taxiways;
        Core::EventQueue& m_eq;
        PenaltyManager& m_penalty_mgr;
        float m_current_time = 0.f;
        const float m_takeoff_delay_lim = 5.f;
    };

}