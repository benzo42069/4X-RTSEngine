#pragma once
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace company::engine {

struct Event {
    std::string type;
    std::uint32_t tick{};
    std::string payload;
};

class EventBus {
public:
    using Handler = std::function<void(const Event&)>;
    void Subscribe(Handler handler);
    void Queue(Event event);
    void DispatchUpTo(std::uint32_t tick);
    const std::vector<Event>& History() const;
private:
    std::vector<Handler> handlers_;
    std::vector<Event> queue_;
    std::vector<Event> history_;
};

} // namespace company::engine
