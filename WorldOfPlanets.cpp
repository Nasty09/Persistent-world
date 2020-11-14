#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "Planet.h"
#include <benchmark/benchmark.h>

/*Определение, на какую планету ведет портал (новую или одну из известных)*/
int definePlanet(int total, int current, std::vector<Planet> world)
{
    int newPlanet = rand() % (total * 2);
    while ((newPlanet == current || (newPlanet < total && world[newPlanet].getEmptyPortal() == -1)))
    {
        newPlanet = rand() % (total * 2); //генерируем случайное число от 0 до общего количества известных планет умноженного на 2 (чтобы повысить вероятность попадания на новую планету)
    }

    if (newPlanet > total)
    {
        newPlanet = total;
    }
    return newPlanet;
}

/*Функция для вывода порталов на текущей планете*/
void portalSelect(Planet planet, std::vector<Planet> world)
{
    std::cout << "Which portal do you choose?\n";
    for (int i = 0; i < planet.getNumOfPortals(); i++) //перебор всех порталов на текущей планете
    {
        std::cout << (i + 1) << ": ";
        if (planet.getPortal(i) == -1)
        {
            std::cout << "unknown\n";
        }
        else
        {
            world[planet.getPortal(i)].OutputInfo();
        }
    }
    std::cout << "Enter 0 for exit.\n";
}


/*Функция для тестирования считывания состояния игры*/
void Test_load(benchmark::State& state)
{
    int currentPlanet = 0;
    std::vector<Planet> knownWorld;
    for (auto _ : state) //часть кода которая тестируется, находится в этом цикле
    {
        std::ifstream is("savegame.cereal", std::ios::binary); //открываем файл
        cereal::BinaryInputArchive arInput(is);
        arInput(currentPlanet, knownWorld); //считываем данные
        is.close();
    }
}
BENCHMARK(Test_load); //объеявление функции, как теста для benchmark

/*Функция для тестирования сохранения состояния игры*/
void Test_save(benchmark::State& state)
{
    int currentPlanet = 0;
    std::vector<Planet> knownWorld;
    std::ifstream is("savegame.cereal", std::ios::binary);
    cereal::BinaryInputArchive arInput(is);
    arInput(currentPlanet, knownWorld);
    is.close();
    for (auto _ : state)
    {
        std::ofstream os("savegame.cereal", std::ios::binary); //открываем файл для записи
        cereal::BinaryOutputArchive arOut(os);
        arOut(currentPlanet, knownWorld); //сохраняем состояние игры
        os.close();
    }
}
BENCHMARK(Test_save);


int main()
{
    int currentPlanet = 0, newPlanet;
    int c = 1, numOfPlanets = 0;
    std::vector<Planet> knownWorld;
    srand(time(0));
    std::ifstream is("savegame.cereal", std::ios::binary);
    if (is)
    {
        char a;
        std::cout << "Do you want restart? [y/n]\n";
        std::cin >> a;
        if (a == 'n')
        {
            cereal::BinaryInputArchive arInput(is);
            arInput(currentPlanet, knownWorld);
            numOfPlanets = Planet::total;
            is.close();
        }
        else
        {
            knownWorld.push_back(Planet());
            numOfPlanets++;
        }
    }
    else
    {
        knownWorld.push_back(Planet());
        numOfPlanets++;
    }
    std::cout << "You are on the Planet:\n";
    knownWorld[currentPlanet].OutputInfo();
    portalSelect(knownWorld[currentPlanet], knownWorld);
    std::cin >> c;
    while (c != 0)
    {
        if ((c - 1) < knownWorld[currentPlanet].getNumOfPortals())
        {
            if (knownWorld[currentPlanet].getPortal(c - 1) == -1)
            {
                newPlanet = definePlanet(numOfPlanets, currentPlanet, knownWorld);
                if (newPlanet == numOfPlanets)
                {
                    knownWorld.push_back(Planet());
                    numOfPlanets++;
                }
                knownWorld[currentPlanet].setPortal(c - 1, newPlanet);
                knownWorld[newPlanet].setPortal(knownWorld[newPlanet].getEmptyPortal(), currentPlanet);
                currentPlanet = newPlanet;
            }
            else if (c != 0)
            {
                currentPlanet = knownWorld[currentPlanet].getPortal(c - 1);
            }
        }
        std::cout << "You are on the Planet:\n";
        knownWorld[currentPlanet].OutputInfo();
        portalSelect(knownWorld[currentPlanet], knownWorld);
        std::cin >> c;
    }
    std::ofstream os("savegame.cereal", std::ios::binary);
    cereal::BinaryOutputArchive arOut(os);
    arOut(currentPlanet,knownWorld);
    os.close();
    benchmark::RunSpecifiedBenchmarks(); //запуск тестов
    return 0;
}
