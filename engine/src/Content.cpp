#include "company/engine/Content.hpp"
#include <fstream>

namespace company::engine {

nlohmann::json LoadJsonFile(const std::string& path) {
    std::ifstream in(path);
    nlohmann::json j;
    in >> j;
    return j;
}

ScenarioDefinition ParseScenario(const nlohmann::json& j) {
    ScenarioDefinition out;
    out.width = j.at("map").at("width").get<std::uint32_t>();
    out.height = j.at("map").at("height").get<std::uint32_t>();
    out.rtsMode = j.value("rtsMode", false);
    return out;
}

} // namespace company::engine
