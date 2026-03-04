#include <doctest/doctest.h>
#include "company/engine/World.hpp"

TEST_CASE("deterministic simulation with same seed") {
    company::engine::World a, b;
    a.Init(42, 16, 16);
    b.Init(42, 16, 16);
    a.rtsMode = true;
    b.rtsMode = true;
    a.units.push_back({1,1,5,5,10});
    b.units.push_back({1,1,5,5,10});
    for (int i=0;i<100;++i) { a.FixedTick(); b.FixedTick(); }
    CHECK(a.units[0].x == b.units[0].x);
    CHECK(a.units[0].y == b.units[0].y);
    CHECK(a.turn == b.turn);
}
