#include "Planet.hpp"
#include "World.hpp"
#include <benchmark/benchmark.h>
#include <fstream>
#include <vector>
#include <iostream>


/*Функция для тестирования считывания состояния игры*/
void Test_load(benchmark::State& state)
{
    World knownWorld(state.range(0));
    std::ofstream os("savegame.cereal", std::ios::binary);
    cereal::BinaryOutputArchive arOut(os);
    arOut(knownWorld);
    os.close();
    for (auto _ : state)
    {
        std::ifstream is("savegame.cereal", std::ios::binary);
        cereal::BinaryInputArchive arInput(is);
        arInput(knownWorld);
        is.close();
    }
}
BENCHMARK(Test_load)->DenseRange(20, 2020, 2000);

/*Функция для тестирования сохранения состояния игры*/
void Test_save(benchmark::State& state)
{
    World knownWorld(state.range(0));
    for (auto _ : state)
    {
        std::ofstream os("savegame.cereal", std::ios::binary);
        cereal::BinaryOutputArchive arOut(os);
        arOut(knownWorld);
        os.close();
    }
}
BENCHMARK(Test_save)->DenseRange(20, 2020, 2000);

int main()
{
    try
    {
    benchmark::RunSpecifiedBenchmarks(); //запуск тестов
    } catch (const std::exception& e) {std::cout << e.what();}
    return 0;
}
