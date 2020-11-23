#ifndef PLANET_HPP
#define PLANET_HPP
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

class Planet
{
    std::string name; //имя планеты
    std::string color; //цвет планеты
    std::vector<int> Portals; //массив порталов (хранятся номера планет, куда ведут соответствующие порталы)
public:
    Planet();
    int getPortal(int num) const; //получение номера планеты, куда ведет портал
    int getNumOfPortals() const; //получение количества порталов на планете
    void setPortal(int num, int val); //задание для портала номера планеты, на которую он ведет
    void OutputInfo() const;
    int getEmptyPortal() const; //поиск пустого портала на планете

    template <class Archive>
    void serialize(Archive& ar) //функция для серриализации и десерриализации класса Planet
    {
        ar(name, color, Portals);
    }
};
#endif
