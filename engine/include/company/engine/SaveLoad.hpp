#pragma once
#include "company/engine/World.hpp"
#include <nlohmann/json.hpp>
#include <string>

namespace company::engine {

nlohmann::json SaveWorld(const World& world);
World LoadWorld(const nlohmann::json& json);
void SaveWorldToFile(const World& world, const std::string& path);
World LoadWorldFromFile(const std::string& path);

} // namespace company::engine
