cmake_minimum_required(VERSION 3.5)

project(WorldOfPlanets LANGUAGES CXX)

find_package(benchmark)

add_executable(${PROJECT_NAME}
    WorldOfPlanets.cpp Planet.cpp
    Planet.h Data.h
    )
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
