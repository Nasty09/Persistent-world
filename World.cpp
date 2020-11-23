#include "World.hpp"
#include <vector>
#include <random>
#include <iostream>

World::World() : world({Planet()}), currentPlanet(0) {}
World::World(int kol) : world({Planet()}), currentPlanet(0)
{
    int newPlanet, c;
    std::mt19937 prng (std::random_device{}());
    while (world.size() < kol)
    {
        std::uniform_int_distribution<std::uint64_t> dist(0, world[currentPlanet].getNumOfPortals() - 1);
        c = dist(prng);
        if (world[currentPlanet].getPortal(c) == -1) //если портал не исследован
        {
            newPlanet = this->definePlanet();
            if (newPlanet == world.size()) //если портал ведет на новую планету
            {
                world.push_back(Planet());
            }
            world[currentPlanet].setPortal(c, newPlanet);
            world[newPlanet].setPortal(world[newPlanet].getEmptyPortal(), currentPlanet);
            currentPlanet = newPlanet;
        }
        else //если портал уже исследован
        {
            currentPlanet = world[currentPlanet].getPortal(c);
        }
    }
}

std::vector<Planet> World::getWorld() const
{
    return world;
}

void World::setWorldPortal(int num, int newPlanet)
{
    world[currentPlanet].setPortal(num, newPlanet);
}

void World::setPlanet(int num)
{
    currentPlanet = num;
}

void World::add(Planet planet)
{
    world.push_back(std::move(planet));
}

int World::definePlanet()
{
    int total = world.size();
    std::mt19937 prng (std::random_device{}());
    std::uniform_int_distribution<std::uint64_t> dist(0, total * 4);
    int newPlanet = dist(prng);
    while ((newPlanet == currentPlanet || (newPlanet < total && world[newPlanet].getEmptyPortal() == -1)))
    {
        newPlanet = dist(prng);
    }

    if (newPlanet > total)
    {
        newPlanet = total;
    }
    return newPlanet;
}

void World::portalSelect()
{
    std::cout << "Which portal do you choose?\n";
    for (int i = 0; i < world[currentPlanet].getNumOfPortals(); i++) //перебор всех порталов на текущей планете
    {
        std::cout << (i + 1) << ": ";
        if (world[currentPlanet].getPortal(i) == -1)
        {
            std::cout << "unknown\n";
        }
        else
        {
            world[world[currentPlanet].getPortal(i)].OutputInfo();
        }
    }
    std::cout << "Enter 0 for exit.\n";
}
