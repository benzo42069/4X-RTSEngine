#include "company/engine/Config.hpp"
#include "company/engine/Content.hpp"
#include "company/engine/SaveLoad.hpp"
#include "company/engine/World.hpp"
#include <iostream>

using namespace company::engine;

int main(int argc, char** argv) {
    const auto cfg = ParseConfig(argc, argv);
    const auto scenarioPath = "data/scenarios/" + cfg.scenario + ".json";
    const auto scenarioJson = LoadJsonFile(scenarioPath);
    const auto scenario = ParseScenario(scenarioJson);

    World world;
    world.Init(cfg.seed, scenario.width, scenario.height);
    world.rtsMode = scenario.rtsMode;
    world.cities.push_back(City{1, 1, 2, 2, 2, 0});
    world.cities.push_back(City{2, 2, 12, 12, 2, 0});
    world.units.push_back(Unit{1, 1, 3, 3, 10});
    world.units.push_back(Unit{2, 2, 10, 10, 10});

    world.events.Subscribe([](const Event& e) {
        std::cout << "[Event] tick=" << e.tick << " type=" << e.type << " payload=" << e.payload << "\n";
    });

    for (std::uint32_t i = 0; i < cfg.maxTicks; ++i) {
        world.FixedTick();
    }

    SaveWorldToFile(world, "savegame.json");
    std::cout << "Finished. Tick=" << world.tick << " Turn=" << world.turn << "\n";
    return 0;
}
