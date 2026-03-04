#pragma once
#include <cstdint>
#include <string>

namespace company::engine {

struct Config {
    bool headless{false};
    std::string scenario{"demo"};
    std::uint32_t seed{123u};
    std::uint32_t maxTicks{200u};
};

Config ParseConfig(int argc, char** argv);

} // namespace company::engine
