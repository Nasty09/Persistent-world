#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <iostream>

class Planet
{
    std::string name; //имя планеты
    std::string color; //цвет планеты
    int numOfPortals; //количество порталов
    int id; //уникальный номер
    std::vector<int> Portals; //массив порталов (хранятся номера планет, куда ведут соответствующие порталы)

    std::string generateName(); //генерация имени планеты
    std::string generateColor(); //генерация цвета планеты
public:
    static int total; //обхщее количество планет
    Planet(); //конструктор создания новой планеты
    ~Planet(){};
    void OutputInfo(); //вывод информации о планете
    int getPortal(int num); //получение номера планеты, куда ведет портал
    int getNumOfPortals(); //получение количества порталов на планете
    void setPortal(int num, int val); //задание для портала номера планеты, на которую он ведет
    int getEmptyPortal(); //поиск пустого портала на планете

    template <class Archive>
    void serialize(Archive& ar) //функция для серриализации и десерриализации класса Planet
    {
        ar(name, color, numOfPortals, id, Portals);
    }
};