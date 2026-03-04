#include "company/engine/Expression.hpp"
#include <stdexcept>

namespace company::engine {

static double ReadValue(const nlohmann::json& expr, const Context& ctx) {
    if (expr.is_number()) return expr.get<double>();
    if (expr.is_string()) {
        auto it = ctx.find(expr.get<std::string>());
        if (it == ctx.end()) throw std::runtime_error("Unknown symbol");
        return it->second;
    }
    if (expr.is_object()) return EvalNumber(expr, ctx);
    throw std::runtime_error("Invalid expression node");
}

double EvalNumber(const nlohmann::json& expr, const Context& ctx) {
    if (!expr.is_object()) return ReadValue(expr, ctx);
    const auto op = expr.at("op").get<std::string>();
    const auto& args = expr.at("args");
    if (op == "add") return ReadValue(args[0], ctx) + ReadValue(args[1], ctx);
    if (op == "sub") return ReadValue(args[0], ctx) - ReadValue(args[1], ctx);
    if (op == "mul") return ReadValue(args[0], ctx) * ReadValue(args[1], ctx);
    if (op == "div") return ReadValue(args[0], ctx) / ReadValue(args[1], ctx);
    throw std::runtime_error("Unknown numeric op");
}

bool EvalBool(const nlohmann::json& expr, const Context& ctx) {
    const auto op = expr.at("op").get<std::string>();
    const auto& args = expr.at("args");
    if (op == "and") return EvalBool(args[0], ctx) && EvalBool(args[1], ctx);
    if (op == "or") return EvalBool(args[0], ctx) || EvalBool(args[1], ctx);
    if (op == "not") return !EvalBool(args[0], ctx);
    if (op == "gt") return ReadValue(args[0], ctx) > ReadValue(args[1], ctx);
    if (op == "lt") return ReadValue(args[0], ctx) < ReadValue(args[1], ctx);
    if (op == "ge") return ReadValue(args[0], ctx) >= ReadValue(args[1], ctx);
    if (op == "le") return ReadValue(args[0], ctx) <= ReadValue(args[1], ctx);
    if (op == "eq") return ReadValue(args[0], ctx) == ReadValue(args[1], ctx);
    throw std::runtime_error("Unknown bool op");
}

} // namespace company::engine
