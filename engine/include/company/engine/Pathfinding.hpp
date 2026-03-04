#pragma once
#include <cstdint>
#include <vector>

namespace company::engine {

struct Grid {
    std::uint32_t width{};
    std::uint32_t height{};
    std::vector<std::uint8_t> cost; // 255 blocked
};

struct NodePos { int x{}; int y{}; };

std::vector<NodePos> FindPath(const Grid& grid, NodePos start, NodePos goal);

} // namespace company::engine
