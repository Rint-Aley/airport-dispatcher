#include <Core/EventQueue.hpp>
#include <Core/LevelManager.hpp>
#include <Logic/Dispatcher.hpp>
#include <Logic/PenaltyManager.hpp>
#include <Persistence/StatisticsManager.hpp>

#include <iostream>
#include <vector>
#include <memory>
#include <thread>

using Clock = std::chrono::steady_clock;
using Duration = std::chrono::duration<double>;

int main(){
    Core::EventQueue eq;

    // в файле 1 уровень пока
    Core::LevelManager lvl_mgr(eq, "../config/levels.json");
    lvl_mgr.load_level(1);

    // настройки текущего уровня
    const auto& planes = lvl_mgr.get_planes();
    auto& runways = lvl_mgr.get_runways();
    auto& taxiways = lvl_mgr.get_taxiways();

    Logic::PenaltyManager penalty_mgr;
    Logic::Dispatcher dispatcher(runways, taxiways, eq, penalty_mgr);
    Persistence::StatisticsManager stats;

    const auto start_time = Clock::now();
    while (!eq.empty()) {
        auto [time, action] = eq.pop();

        // чтобы очередь ивентов соответсовала реальному времени
        const auto target_time = start_time + Duration(time);
        if (target_time > Clock::now())
            std::this_thread::sleep_until(target_time);
        dispatcher.set_time(time);

        for (auto& plane : planes) {
            if (plane->role() == Core::FlightRole::Arrival &&
                plane->state() == Core::FlightState::QueuedForLanding) {
                dispatcher.process_landing(plane.get());
            }
            else if (plane->role()==Core::FlightRole::Departure &&
                     plane->state()==Core::FlightState::QueuedForTakeoff) {
                dispatcher.process_takeoff(plane.get());
            }
        }
        action();
    }

    // в будущем при краше уровень проигран
    // (но надо сделать, чтобы при переигровке как то условия менялись, а то уровень не пройдётся никогда)
    int cc=0;
    for (auto& plane : planes) if (plane->state() == Core::FlightState::Crashed) ++cc;
    std::cout << "\n[debug] CRASH COUNT: " << cc;

    // простейший показ
    stats.add_scores(penalty_mgr.landing_holds, penalty_mgr.takeoff_delays);
    stats.print_leaderboard();
    return 0;
}
