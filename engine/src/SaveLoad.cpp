#include "company/engine/SaveLoad.hpp"
#include <fstream>

namespace company::engine {

nlohmann::json SaveWorld(const World& world) {
    nlohmann::json j;
    j["version"] = 1;
    j["tick"] = world.tick;
    j["turn"] = world.turn;
    j["rtsMode"] = world.rtsMode;
    j["width"] = world.width;
    j["height"] = world.height;
    j["seed"] = world.rng.MasterSeed();
    for (const auto& u : world.units) {
        j["units"].push_back({{"id", u.id}, {"faction", u.faction}, {"x", u.x}, {"y", u.y}, {"hp", u.hp}});
    }
    for (const auto& c : world.cities) {
        j["cities"].push_back({{"id", c.id}, {"faction", c.faction}, {"x", c.x}, {"y", c.y}, {"population", c.population}, {"food", c.food}});
    }
    return j;
}

World LoadWorld(const nlohmann::json& j) {
    World w;
    w.Init(j.at("seed").get<std::uint32_t>(), j.at("width").get<std::uint32_t>(), j.at("height").get<std::uint32_t>());
    w.tick = j.at("tick").get<std::uint32_t>();
    w.turn = j.at("turn").get<std::uint32_t>();
    w.rtsMode = j.at("rtsMode").get<bool>();
    if (j.contains("units")) {
        for (const auto& u : j.at("units")) {
            w.units.push_back(Unit{u.at("id").get<std::uint32_t>(), u.at("faction").get<std::uint32_t>(), u.at("x").get<int>(), u.at("y").get<int>(), u.at("hp").get<int>()});
        }
    }
    if (j.contains("cities")) {
        for (const auto& c : j.at("cities")) {
            w.cities.push_back(City{c.at("id").get<std::uint32_t>(), c.at("faction").get<std::uint32_t>(), c.at("x").get<int>(), c.at("y").get<int>(), c.at("population").get<int>(), c.at("food").get<int>()});
        }
    }
    return w;
}

void SaveWorldToFile(const World& world, const std::string& path) {
    std::ofstream out(path);
    out << SaveWorld(world).dump(2);
}

World LoadWorldFromFile(const std::string& path) {
    std::ifstream in(path);
    nlohmann::json j;
    in >> j;
    return LoadWorld(j);
}

} // namespace company::engine
