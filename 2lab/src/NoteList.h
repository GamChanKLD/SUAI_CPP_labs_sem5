#ifndef NOTELIST_H
#define NOTELIST_H

#include <iostream>
#include <string>
#include "Note.h"

// Динамический список записей NOTE (без STL-контейнеров).
// Хранит массив указателей на объекты, массив расширяется при необходимости.
class NoteList {
private:
    Note** items_;
    int size_;
    int capacity_;

    void grow();   // увеличивает вместимость в 2 раза

public:
    // Конструкторы и деструктор (с выводом сообщений)
    NoteList();
    explicit NoteList(int capacity);
    NoteList(const NoteList& other);
    ~NoteList();

    NoteList& operator=(const NoteList& other);

    // Доступ по индексу (с проверкой границ)
    Note& operator[](int index);
    const Note& operator[](int index) const;

    // Добавление в конец
    NoteList& operator+=(const Note& note);
    void add(const Note& note);

    int getSize() const;
    bool isEmpty() const;

    void insert(int position, const Note& note);   // вставка на любую позицию (0..size)
    void remove(int index);                         // удаление по индексу
    void clear();

    void sortByPhonePrefix();                       // по возрастанию первых трёх цифр телефона
    int findBySurname(const std::string& surname, int from = 0) const;   // индекс или -1

    friend std::ostream& operator<<(std::ostream& os, const NoteList& list);
};

#endif
