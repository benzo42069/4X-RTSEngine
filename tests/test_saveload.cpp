#include <doctest/doctest.h>
#include "company/engine/SaveLoad.hpp"

TEST_CASE("save and load preserves world") {
    company::engine::World w;
    w.Init(7, 8, 8);
    w.rtsMode = true;
    w.units.push_back({1,1,2,3,9});
    for (int i=0;i<20;++i) w.FixedTick();
    auto j = company::engine::SaveWorld(w);
    auto w2 = company::engine::LoadWorld(j);
    CHECK(w.tick == w2.tick);
    CHECK(w.turn == w2.turn);
    REQUIRE(w2.units.size() == 1);
    CHECK(w.units[0].x == w2.units[0].x);
}
