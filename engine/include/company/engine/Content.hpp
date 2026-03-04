#pragma once
#include <nlohmann/json.hpp>
#include <string>

namespace company::engine {

struct ScenarioDefinition {
    std::uint32_t width{16};
    std::uint32_t height{16};
    bool rtsMode{false};
};

nlohmann::json LoadJsonFile(const std::string& path);
ScenarioDefinition ParseScenario(const nlohmann::json& j);

} // namespace company::engine
