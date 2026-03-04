#include "company/engine/World.hpp"

namespace company::engine {

void World::Init(std::uint32_t seed, std::uint32_t w, std::uint32_t h) {
    width = w;
    height = h;
    tick = 0;
    turn = 0;
    rng = RngService(seed);
    tiles.assign(width * height, Tile{});
}

void World::FixedTick() {
    ++tick;
    if (tick % 10 == 0) {
        ++turn;
        for (auto& city : cities) {
            city.food += 2;
            if (city.food >= 10) {
                city.food -= 10;
                city.population += 1;
                events.Queue(Event{"city_growth", tick, std::to_string(city.id)});
            }
        }
    }

    if (rtsMode) {
        for (auto& unit : units) {
            auto& stream = rng.Stream(unit.id);
            int dir = static_cast<int>(stream.NextU32() % 4);
            if (dir == 0 && unit.x + 1 < static_cast<int>(width)) unit.x++;
            if (dir == 1 && unit.x - 1 >= 0) unit.x--;
            if (dir == 2 && unit.y + 1 < static_cast<int>(height)) unit.y++;
            if (dir == 3 && unit.y - 1 >= 0) unit.y--;
        }
    }

    events.DispatchUpTo(tick);
}

} // namespace company::engine
