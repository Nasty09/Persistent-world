#include <iostream>
#include "Planet.hpp"
#include "World.hpp"
#include <fstream>
#include <vector>

int main()
{
    int currentPlanet = 0, newPlanet, c = 1;
    World knownWorld;
    {
        std::ifstream is("savegame.cereal", std::ios::binary);
        if (is)
        {
            char a;
            std::cout << "Do you want restart? [y/n]\n";
            std::cin >> a;
            if (a == 'n')
            {
                cereal::BinaryInputArchive arInput(is);
                arInput(knownWorld);
            }
            else
            {
                knownWorld.add(Planet());
            }
        }
        else
        {
            knownWorld.add(Planet());
        }
    }
    std::cout << "You are on the Planet:\n";
    knownWorld.getWorld()[currentPlanet].OutputInfo();
    knownWorld.portalSelect();
    std::cin >> c;
    while (c != 0)
    {
        if (0 < c && c <= knownWorld.getWorld()[currentPlanet].getNumOfPortals()) //если выбран корректный номер нортала
        {
            if (knownWorld.getWorld()[currentPlanet].getPortal(c - 1) == -1) //если портал не исследован
            {
                newPlanet = knownWorld.definePlanet();
                if (newPlanet == knownWorld.getWorld().size()) //если портал ведет на новую планету
                {
                    knownWorld.add(Planet());
                }
                knownWorld.setWorldPortal(c - 1, newPlanet);
                knownWorld.setPlanet(newPlanet);
                knownWorld.setWorldPortal(knownWorld.getWorld()[newPlanet].getEmptyPortal(), currentPlanet);
                currentPlanet = newPlanet;
            }
            else//если портал уже исследован
            {
                currentPlanet = knownWorld.getWorld()[currentPlanet].getPortal(c - 1);
                knownWorld.setPlanet(currentPlanet);
            }
        }
        else
            std::cout << "\nThis portal doesn't exist.\n" << "Choose another one\n\n";
        std::cout << "You are on the Planet:\n";
        knownWorld.getWorld()[currentPlanet].OutputInfo();
        knownWorld.portalSelect();
        std::cin >> c;
    }
    std::ofstream os("savegame.cereal", std::ios::binary);
    cereal::BinaryOutputArchive arOut(os);
    arOut(knownWorld);
    return 0;
}
