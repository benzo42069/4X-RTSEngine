# 4X-RTS Engine (Deterministic Core)

Standalone C++20 strategy engine scaffold focused on deterministic simulation and data-driven scenario loading.

## Features in this deliverable
- Fixed-step deterministic world tick.
- 4X turn counter layered over fixed ticks.
- RTS mode toggle with deterministic per-unit RNG stream movement.
- Data-driven scenario loading from JSON.
- Type-safe queued event bus.
- Deterministic save/load to JSON with version field.
- JSON expression evaluation for gameplay rules.
- A* grid pathfinding.
- Doctest-based automated tests: determinism, save/load, expression, pathfinding.

## Build
```bash
cmake -S . -B build -DENGINE_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

## Run demo
```bash
./build/Game --headless --scenario demo --seed 123 --ticks 200
```
