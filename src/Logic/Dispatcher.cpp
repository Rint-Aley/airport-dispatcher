#include "Logic/Dispatcher.hpp"
#include <iostream>

using namespace Logic;
using namespace Core;

Dispatcher::Dispatcher(std::vector<Runway>& runways, TaxiwayManager& taxiways,
    EventQueue& eq, PenaltyManager& penalty_mgr)
    : m_runways(runways), m_taxiways(taxiways), m_eq(eq), m_penalty_mgr(penalty_mgr) {}

std::optional<size_t> Dispatcher::find_available_runway(const int req_len) const {
    for (size_t i = 0; i < m_runways.size(); ++i) {
        if (m_runways[i].can_serve(req_len))
            return i;
    }
    return std::nullopt;
}

void Dispatcher::process_landing(IAirplane* plane) {
    std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id() << " request landing\n";

    const auto idx = find_available_runway(plane->required_runway_length());
    if (!idx) {
        // второй круг или краш
        plane->inc_holding_count();
        m_penalty_mgr.on_hold();
        if (plane->holding_count() > plane->max_holding_circles()) {
            plane->set_state(FlightState::Crashed);
            std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id()
                      << " -> Crash (too many holds: " << plane->holding_count() << ")\n";
        } else {
            plane->set_state(FlightState::Holding);
            std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id()
                      << " holding... (" << plane->holding_count() << ")\n";
            m_eq.schedule(m_current_time+1.f, [this,plane]{ process_landing(plane); });
        }
        return;
    }

    // найдена ВПП
    m_runways[*idx].reserve();
    plane->set_state(FlightState::Landing);
    std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id()
              << " -> Assigned runway: " << m_runways[*idx].id << "\n";
    m_eq.schedule(m_current_time + plane->operation_time(), [this,plane,idx] {
        m_runways[*idx].release();
        plane->set_state(FlightState::Taxiing);
        std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id() << " Landed!\n";
    });
}

void Dispatcher::process_takeoff(IAirplane* plane) {
    if (plane->state() != FlightState::QueuedForTakeoff)
        return;

    std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id() << " request takeoff\n";

    const auto idx = find_available_runway(plane->required_runway_length());
    if (!idx) {
        // нет полосы
        std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id()
                  << " no available runway for now\n";
        m_penalty_mgr.on_delay();
        m_eq.schedule(m_current_time+1.f, [this,plane]{ process_takeoff(plane); });
        return;
    }

    // найдена ВПП
    m_runways[*idx].reserve();
    plane->set_state(FlightState::TakingOff);
    std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id()
              << " Using runway " << m_runways[*idx].id << "\n";
    m_eq.schedule(m_current_time+plane->operation_time(), [this,plane,idx]{
        m_runways[*idx].release();
        plane->set_state(FlightState::Departed);
        std::cout << "[" << m_current_time << "] " << plane->type_name() << " #" << plane->id() << " -> Took off\n";
    });
}
