#ifndef WORLD_HPP
#define WORLD_HPP
#include "Planet.hpp"

class World
{
    std::vector<Planet> world;
    int currentPlanet;
public:
    World();
    World(int kol);
    std::vector<Planet> getWorld() const;
    void setWorldPortal(int num, int newPlanet);
    void setPlanet(int num);
    void add(Planet planet);
    int definePlanet();//Определение, на какую планету ведет портал (новую или одну из известных)
    void portalSelect();

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(currentPlanet, world);
    }
};
#endif
