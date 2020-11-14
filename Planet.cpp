#include "Planet.h"
#include "Data.h" //массивы имен и цветов планет (допустимые значения)

int Planet::total = 0; //количество известных планет

Planet::Planet()
{
    id = total;
    total++;
    name = generateName();
    color = generateColor();
    numOfPortals = rand() % 10 + 1;
    for (int i = 0; i < numOfPortals; i++)
    {
        Portals.push_back(-1);
    }
}

std::string Planet::generateName()
{
    return PlanetsName[rand() % 38];
}

std::string Planet::generateColor()
{
    return ColorNames[rand() % 38];
}

void Planet::OutputInfo()
{
    std::cout << "Name: " << name << ". "
              << "Color: " << color << ". "
              << "There are " << numOfPortals << " portals here.\n";
}

int Planet::getPortal(int num)
{
    return Portals[num];
}

int Planet::getNumOfPortals()
{
    return numOfPortals;
}

void Planet::setPortal(int num, int val)
{
    Portals[num] = val;
}

int Planet::getEmptyPortal()
{
    int i;
    for (i = 0; i < numOfPortals && Portals[i] != -1; i++);
    if (i == numOfPortals)
        return -1;
    else
        return i;
}
