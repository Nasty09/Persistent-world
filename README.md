# Persistent-world
Домашнее задание по "Современные технологии программирования и обработки информации"

Люди исследуют планеты, соединённые порталами. Каждый портал двусторонний и соединяет две планеты.
Планета характеризуется именем, цветом и имеющимися на ней порталами (минимум 1).
Каждый портал соединён с порталом на другой планете, соединения двунаправленные и стабильные,
но до первого прохода через портал его местоназначение неизвестно.
Игрок начинает на домашней планете. Попадая на планету, разведка предоставляет все её характеристики.
Каждый ход игрок указывает, в какой портал идёт дальше. Первый проход через не исследованный портал
может вывести на один из не исследованных порталов на других известных планетах, или на новую планету.
Реализовать путешествие по подобным образом устроенному миру с возможностью выхода из программы
с сериализацией известной части мира в файл, чтобы десериализовать при следующем запуске.

Используются Cereal и google.benchmark


## Results
Результаты, полученные на больших значениях начиная с 20, с шагом в 2000.
![Image of Big results](https://github.com/Nasty09/Persistent-world/blob/main/Big%20results.png)

Результаты, полученные на маленьких занчениях начиная с 2, с шагом в 20
![Image of Small results](https://github.com/Nasty09/Persistent-world/blob/main/Small%20results.png)
