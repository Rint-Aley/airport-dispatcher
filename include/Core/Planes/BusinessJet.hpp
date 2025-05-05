#pragma once

namespace Core::Planes {

    class BusinessJet final : public IAirplane {
    public:
        explicit BusinessJet(const int id, const FlightRole role) :
            m_id(id), m_role(role),
            m_state(role == FlightRole::Arrival ? FlightState::FlyingIn :
                                                  FlightState::Parked) {}

        [[nodiscard]] int id() const override { return m_id; }
        [[nodiscard]] std::string type_name() const override { return "BusinessJet"; }
        [[nodiscard]] int required_runway_length() const override { return 120; }
        [[nodiscard]] float operation_time() const override { return 2.5f; }
        [[nodiscard]] int max_holding_circles() const override { return 2; }

        [[nodiscard]] FlightRole role() const override { return m_role; }
        [[nodiscard]] FlightState state() const override { return m_state; }
        void set_state(const FlightState new_state) override { m_state = new_state; }
        [[nodiscard]] int holding_count() const override { return m_holding_count; }
        void inc_holding_count() override { ++m_holding_count; }

    private:
        int m_id;
        FlightRole m_role;
        FlightState m_state;
        int m_holding_count = 0;
    };

}