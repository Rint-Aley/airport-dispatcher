#pragma once

#include <string>

namespace Core {

    enum class FlightRole {
        Arrival,  // на посадку
        Departure // на взлёт
    };

    enum class FlightState {
        Parked,             // запаркован
        FlyingIn,           // в полете
        QueuedForLanding,   // в очереди на посадку
        Holding,            // на n-ом круге
        Landing,            // приземляется
        Taxiing,            // приземлился - ищет рулежку (не реализовано)
        QueuedForTakeoff,   // в очереди на взлёт
        TakingOff,          // взлетает
        Departed,           // взлетел
        Crashed             // краш
    };


    class IAirplane {
    public:
        virtual ~IAirplane() = default;

        [[nodiscard]] virtual int id() const = 0; // айди самолета (из ктора самолета)
        [[nodiscard]] virtual std::string type_name() const = 0; // перезаписывается конкретным типом
        [[nodiscard]] virtual int required_runway_length() const = 0; // перезаписывается конкретным типом
        [[nodiscard]] virtual float operation_time() const = 0; // перезаписывается конкретным типом
        [[nodiscard]] virtual int max_holding_circles() const = 0; // перезаписывается конкретным типом

        [[nodiscard]] virtual FlightRole role() const = 0; // роль (из ктора)
        [[nodiscard]] virtual FlightState state() const = 0; // по умолчанию FlyingIn / Parked
        virtual void set_state(FlightState p) = 0;
        [[nodiscard]] virtual int holding_count() const = 0;
        virtual void inc_holding_count() = 0;
    };

}
