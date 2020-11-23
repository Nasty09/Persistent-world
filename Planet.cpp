#include "Planet.hpp"
#include <random>
#include <iostream>

std::vector<std::string> PlanetsName = { "Mercury","Venus","Earth","Mars","Jupiter","Saturn","Uranus",
                                         "Neptune","Pluto","Nebula","Comet","Asteroid","Sun","Moon","Star",
                                         "Meteor","Andromeda","Galaxy","Orbit","Universe","Interstallar",
                                         "Crater","Supernova","Rocket","Matter","Black Hole","Vacuum","Aries",
                                         "Taurus","Virgo","Libra","Cancer","Gemini","Scorpio","Sagittarius",
                                         "Capricorn","Pisces","Aquarius","Leo"};

std::vector<std::string> ColorNames = { "white","black","gray","silver","red","blue","green","yellow",
                                        "brown","orange","pink","purple","violet","beige","scarlet","golden",
                                        "turquoise","emerald","coral","copper","olive","lilac","khaki","azure",
                                        "amber","sand","vinous","chocolate","ivory","salmon","fuchsia","lavender",
                                        "plum","indigo","maroon","crimson","teal","aquamarine","magenta" };

Planet::Planet()
{
    std::mt19937 prng (std::random_device{}());
    std::uniform_int_distribution<uint> dist(0, PlanetsName.size() - 1), dist1(0,ColorNames.size() - 1), dist2(2,10);
    name = PlanetsName[dist(prng)];
    color = ColorNames[dist1(prng)];
    Portals.assign(dist2(prng),-1);
}

int Planet::getPortal(int num) const
{
    return Portals[num];
}

int Planet::getNumOfPortals() const
{
    return Portals.size();
}

void Planet::setPortal(int num, int val)
{
    Portals[num] = val;
}

void Planet::OutputInfo() const
{
    std::cout << "Name: " << name << ". "
              << "Color: " << color << ". "
              << "There are " << Portals.size() << " portals here.\n";
}

int Planet::getEmptyPortal() const
{
    int i, numOfPortals = Portals.size();
    for (i = 0; i < numOfPortals && Portals[i] != -1; i++);
    if (i == numOfPortals)
        return -1;
    else
        return i;
}
