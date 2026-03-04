cmake_minimum_required(VERSION 3.28)
project(4XRTSEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENGINE_BUILD_TESTS "Build unit tests" ON)

add_library(engine
    engine/src/Config.cpp
    engine/src/Rng.cpp
    engine/src/Expression.cpp
    engine/src/EventBus.cpp
    engine/src/Pathfinding.cpp
    engine/src/World.cpp
    engine/src/SaveLoad.cpp
    engine/src/Content.cpp
)

target_include_directories(engine PUBLIC
    engine/include
    third_party
)

if (MSVC)
  target_compile_options(engine PRIVATE /W4 /permissive-)
else()
  target_compile_options(engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(Game game/src/main.cpp)
target_link_libraries(Game PRIVATE engine)

if(ENGINE_BUILD_TESTS)
  enable_testing()
  add_executable(engine_tests
    tests/test_main.cpp
    tests/test_determinism.cpp
    tests/test_saveload.cpp
    tests/test_expression.cpp
    tests/test_pathfinding.cpp
  )
  target_link_libraries(engine_tests PRIVATE engine)
  add_test(NAME engine_tests COMMAND engine_tests)
endif()

foreach(dir assets data)
  add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/${dir}
            $<TARGET_FILE_DIR:Game>/${dir})
endforeach()
