#pragma once

namespace Core {

    /// пока так
    struct Runway {
        int id{};
        int length{};
        bool busy = false;

        [[nodiscard]] bool can_serve(const int req) const {
            return !busy && length >= req;
        }
        void reserve() { busy = true; }
        void release() { busy = false; }
    };

}