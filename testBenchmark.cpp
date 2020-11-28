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
        {
            World new_World;
            std::ifstream is("savegame.cereal", std::ios::binary);
            cereal::BinaryInputArchive arInput(is);
            arInput(new_World);
            state.PauseTiming();
        }
        state.ResumeTiming();
    }
}
BENCHMARK(Test_load)->DenseRange(2, 2002, 20);

/*Функция для тестирования сохранения состояния игры*/
void Test_save(benchmark::State& state)
{
    World knownWorld(state.range(0));
    for (auto _ : state)
    {
        std::ofstream os("savegame.cereal", std::ios::binary);
        cereal::BinaryOutputArchive arOut(os);
        arOut(knownWorld);
    }
}
BENCHMARK(Test_save)->DenseRange(2, 2002, 20);

int main()
{
    benchmark::RunSpecifiedBenchmarks(); //запуск тестов
    return 0;
}
