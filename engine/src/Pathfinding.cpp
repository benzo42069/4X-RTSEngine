#include "company/engine/Pathfinding.hpp"
#include <algorithm>
#include <limits>
#include <queue>

namespace company::engine {

static int Idx(const Grid& g, int x, int y) { return y * static_cast<int>(g.width) + x; }
static bool In(const Grid& g, int x, int y) { return x >= 0 && y >= 0 && x < static_cast<int>(g.width) && y < static_cast<int>(g.height); }
static int Heuristic(NodePos a, NodePos b) { return std::abs(a.x - b.x) + std::abs(a.y - b.y); }

std::vector<NodePos> FindPath(const Grid& grid, NodePos start, NodePos goal) {
    const int n = static_cast<int>(grid.width * grid.height);
    std::vector<int> gscore(n, std::numeric_limits<int>::max());
    std::vector<int> parent(n, -1);
    using QN = std::pair<int, int>;
    std::priority_queue<QN, std::vector<QN>, std::greater<>> open;

    int s = Idx(grid, start.x, start.y);
    int t = Idx(grid, goal.x, goal.y);
    gscore[s] = 0;
    open.push({Heuristic(start, goal), s});

    constexpr int dx[4] = {1, -1, 0, 0};
    constexpr int dy[4] = {0, 0, 1, -1};

    while (!open.empty()) {
        auto [_, cur] = open.top();
        open.pop();
        if (cur == t) break;
        int cx = cur % static_cast<int>(grid.width);
        int cy = cur / static_cast<int>(grid.width);
        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i], ny = cy + dy[i];
            if (!In(grid, nx, ny)) continue;
            int ni = Idx(grid, nx, ny);
            auto c = grid.cost[ni];
            if (c == 255) continue;
            int cand = gscore[cur] + c;
            if (cand < gscore[ni]) {
                gscore[ni] = cand;
                parent[ni] = cur;
                open.push({cand + Heuristic({nx, ny}, goal), ni});
            }
        }
    }

    if (parent[t] == -1 && s != t) return {};
    std::vector<NodePos> path;
    for (int at = t; at != -1; at = parent[at]) {
        path.push_back({at % static_cast<int>(grid.width), at / static_cast<int>(grid.width)});
        if (at == s) break;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace company::engine
