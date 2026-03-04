#pragma once
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

namespace company::engine {

using Context = std::unordered_map<std::string, double>;

double EvalNumber(const nlohmann::json& expr, const Context& ctx);
bool EvalBool(const nlohmann::json& expr, const Context& ctx);

} // namespace company::engine
