#include "company/engine/Config.hpp"

namespace company::engine {

Config ParseConfig(int argc, char** argv) {
    Config cfg;
    for (int i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];
        if (arg == "--headless") {
            cfg.headless = true;
        } else if (arg == "--scenario" && i + 1 < argc) {
            cfg.scenario = argv[++i];
        } else if (arg == "--seed" && i + 1 < argc) {
            cfg.seed = static_cast<std::uint32_t>(std::stoul(argv[++i]));
        } else if (arg == "--ticks" && i + 1 < argc) {
            cfg.maxTicks = static_cast<std::uint32_t>(std::stoul(argv[++i]));
        }
    }
    return cfg;
}

} // namespace company::engine
