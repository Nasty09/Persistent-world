cmake_minimum_required(VERSION 3.5)

project(WorldOfPlanets LANGUAGES CXX)

find_package(benchmark REQUIRED)

add_library(shared Planet.cpp World.cpp Planet.hpp World.hpp)

add_executable(test testBenchmark.cpp)

add_executable(game WorldOfPlanets.cpp)

target_link_libraries(test shared)

target_link_libraries(game shared)

target_link_libraries(test shared benchmark::benchmark)
