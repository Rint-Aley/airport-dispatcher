#include <Core/EventQueue.hpp>

using namespace Core;

void EventQueue::schedule(const float time, std::function<void()> action) {
    m_heap.push(Event{time, std::move(action)});
}

bool EventQueue::empty() const {
    return m_heap.empty();
}

Event EventQueue::pop() {
    auto e = m_heap.top();
    m_heap.pop();
    return e;
}