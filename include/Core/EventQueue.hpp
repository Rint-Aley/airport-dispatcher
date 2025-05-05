#pragma once

#include <queue>
#include <functional>

namespace Core {

    struct Event {
        float time;
        std::function<void()> action;
        bool operator>(Event const& o) const { return time > o.time; }
    };

    class EventQueue {
    public:
        // запланировать функцию к определенному времени
        void schedule(float time, std::function<void()> action);

        // default for priority_queue
        [[nodiscard]] bool empty() const;

        // default for priority_queue
        Event pop();

    private:
        std::priority_queue<Event, std::vector<Event>, std::greater<>> m_heap;
    };

}