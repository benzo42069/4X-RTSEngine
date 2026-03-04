#include <doctest/doctest.h>
#include "company/engine/Pathfinding.hpp"

TEST_CASE("pathfinding avoids blocked cells") {
    company::engine::Grid g;
    g.width = 5;
    g.height = 5;
    g.cost.assign(25, 1);
    g.cost[2 + 1 * 5] = 255;
    auto path = company::engine::FindPath(g, {0,0}, {4,4});
    CHECK(!path.empty());
    CHECK(path.front().x == 0);
    CHECK(path.back().x == 4);
}
