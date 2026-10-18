#pragma once
#include "Base.h"

// Контейнер (динамический массив указателей на Base) без STL
class Keeper {
    Base** items;
    int count;
    int capacity;
    void grow();
public:
    Keeper();
    explicit Keeper(int capacity);
    Keeper(const Keeper& other);
    ~Keeper();
    Keeper& operator=(const Keeper& other);

    int getCount() const;
    int getCapacity() const;

    void add(Base* item);              // Keeper становится владельцем объекта
    void remove(int index);            // удаление по индексу (0..count-1)
    void clear();
    Base& operator[](int index);
    const Base& operator[](int index) const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    friend std::ostream& operator<<(std::ostream& os, const Keeper& k);
};
