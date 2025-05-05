#pragma once

namespace Logic {

    /// пока так
    struct PenaltyManager {
        int landing_holds  = 0;
        int takeoff_delays = 0;
        void on_hold() { ++landing_holds; }
        void on_delay() { ++takeoff_delays; }
    };

}