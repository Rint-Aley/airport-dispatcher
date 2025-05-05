#pragma once

#include <vector>
#include <iostream>

namespace Persistence {

    struct StatisticsManager {
        std::vector<std::pair<int, int>> scores;
        void add_scores(const int landing_holds, const int takeoff_delays) {
            scores.emplace_back(landing_holds, takeoff_delays);
        }

        void print_leaderboard() const {
            std::cout << "\n=== Leaderboard ===\n";
            for (const auto [landing_holds, takeoff_delays] : scores)
                std::cout << "Landing holds: " << landing_holds << " | Takeoff delays: " << takeoff_delays << "\n";
        }
    };

}