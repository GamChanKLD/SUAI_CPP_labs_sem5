#pragma once
#include <iostream>
#include <string>

// Абстрактный базовый класс элементов конференции
class Base {
public:
    Base();
    Base(const Base& other);
    virtual ~Base();
    Base& operator=(const Base& other);

    virtual void print(std::ostream& os) const = 0;   // вывод в поток
    virtual void save(std::ostream& os) const = 0;    // сохранение полей в файл
    virtual void load(std::istream& is) = 0;          // загрузка полей из файла
    virtual void edit() = 0;                          // интерактивное изменение
    virtual Base* clone() const = 0;                  // виртуальное копирование
    virtual std::string typeName() const = 0;         // имя типа (метка в файле)

    friend std::ostream& operator<<(std::ostream& os, const Base& b);
};
