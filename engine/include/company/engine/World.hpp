#pragma once
#include "company/engine/EventBus.hpp"
#include "company/engine/Rng.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace company::engine {

struct Unit {
    std::uint32_t id{};
    std::uint32_t faction{};
    int x{};
    int y{};
    int hp{10};
};

struct City {
    std::uint32_t id{};
    std::uint32_t faction{};
    int x{};
    int y{};
    int population{1};
    int food{0};
};

struct Tile {
    std::string terrain{"plains"};
    std::uint32_t owner{0};
};

struct World {
    std::uint32_t tick{0};
    std::uint32_t turn{0};
    bool rtsMode{false};
    std::uint32_t width{16};
    std::uint32_t height{16};
    std::vector<Tile> tiles;
    std::vector<Unit> units;
    std::vector<City> cities;
    EventBus events;
    RngService rng{1};

    void Init(std::uint32_t seed, std::uint32_t w, std::uint32_t h);
    void FixedTick();
};

} // namespace company::engine
