#include "company/engine/EventBus.hpp"
#include <algorithm>

namespace company::engine {

void EventBus::Subscribe(Handler handler) { handlers_.push_back(std::move(handler)); }

void EventBus::Queue(Event event) { queue_.push_back(std::move(event)); }

void EventBus::DispatchUpTo(std::uint32_t tick) {
    std::stable_sort(queue_.begin(), queue_.end(), [](const Event& a, const Event& b) { return a.tick < b.tick; });
    std::vector<Event> rem;
    rem.reserve(queue_.size());
    for (const auto& event : queue_) {
        if (event.tick <= tick) {
            history_.push_back(event);
            for (const auto& h : handlers_) h(event);
        } else {
            rem.push_back(event);
        }
    }
    queue_.swap(rem);
}

const std::vector<Event>& EventBus::History() const { return history_; }

} // namespace company::engine
