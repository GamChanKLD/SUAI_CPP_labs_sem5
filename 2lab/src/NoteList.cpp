#include "NoteList.h"
#include "Exceptions.h"

using namespace std;

// ---------- Конструкторы и деструктор ----------

NoteList::NoteList() : items_(nullptr), size_(0), capacity_(4) {
    items_ = new Note*[capacity_];
    cout << "[NOTELIST] Вызван конструктор без параметров" << endl;
}

NoteList::NoteList(int capacity) : items_(nullptr), size_(0), capacity_(capacity) {
    if (capacity_ < 1) capacity_ = 1;
    items_ = new Note*[capacity_];
    cout << "[NOTELIST] Вызван конструктор с параметрами (вместимость: " << capacity_ << ")" << endl;
}

NoteList::NoteList(const NoteList& other)
    : items_(nullptr), size_(other.size_), capacity_(other.capacity_) {
    items_ = new Note*[capacity_];
    for (int i = 0; i < size_; i++) items_[i] = new Note(*other.items_[i]);
    cout << "[NOTELIST] Вызван конструктор копирования (записей: " << size_ << ")" << endl;
}

NoteList::~NoteList() {
    cout << "[NOTELIST] Вызван деструктор (записей: " << size_ << ")" << endl;
    for (int i = 0; i < size_; i++) delete items_[i];
    delete[] items_;
}

NoteList& NoteList::operator=(const NoteList& other) {
    if (this != &other) {
        for (int i = 0; i < size_; i++) delete items_[i];
        delete[] items_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        items_ = new Note*[capacity_];
        for (int i = 0; i < size_; i++) items_[i] = new Note(*other.items_[i]);
    }
    return *this;
}

// ---------- Внутренние методы ----------

void NoteList::grow() {
    int newCapacity = capacity_ * 2;
    Note** newItems = new Note*[newCapacity];
    for (int i = 0; i < size_; i++) newItems[i] = items_[i];
    delete[] items_;
    items_ = newItems;
    capacity_ = newCapacity;
}

// ---------- Доступ ----------

Note& NoteList::operator[](int index) {
    if (index < 0 || index >= size_) throw IndexOutOfRangeException(index, size_);
    return *items_[index];
}

const Note& NoteList::operator[](int index) const {
    if (index < 0 || index >= size_) throw IndexOutOfRangeException(index, size_);
    return *items_[index];
}

int NoteList::getSize() const { return size_; }
bool NoteList::isEmpty() const { return size_ == 0; }

// ---------- Изменение списка ----------

void NoteList::add(const Note& note) {
    insert(size_, note);
}

NoteList& NoteList::operator+=(const Note& note) {
    add(note);
    return *this;
}

void NoteList::insert(int position, const Note& note) {
    if (position < 0 || position > size_) throw IndexOutOfRangeException(position, size_);
    if (size_ == capacity_) grow();
    Note* copy = new Note(note);
    for (int i = size_; i > position; i--) items_[i] = items_[i - 1];
    items_[position] = copy;
    size_++;
}

void NoteList::remove(int index) {
    if (size_ == 0) throw EmptyListException();
    if (index < 0 || index >= size_) throw IndexOutOfRangeException(index, size_);
    delete items_[index];
    for (int i = index; i < size_ - 1; i++) items_[i] = items_[i + 1];
    size_--;
}

void NoteList::clear() {
    for (int i = 0; i < size_; i++) delete items_[i];
    size_ = 0;
}

// ---------- Сортировка и поиск ----------

void NoteList::sortByPhonePrefix() {
    if (size_ == 0) throw EmptyListException();
    // сортировка вставками (устойчивая), переставляем только указатели
    for (int i = 1; i < size_; i++) {
        Note* current = items_[i];
        int j = i - 1;
        while (j >= 0 && *current < *items_[j]) {
            items_[j + 1] = items_[j];
            j--;
        }
        items_[j + 1] = current;
    }
}

int NoteList::findBySurname(const string& surname, int from) const {
    for (int i = (from < 0 ? 0 : from); i < size_; i++) {
        if (items_[i]->getSurname() == surname) return i;
    }
    return -1;
}

// ---------- Вывод ----------

ostream& operator<<(ostream& os, const NoteList& list) {
    if (list.size_ == 0) {
        os << "Список записей пуст" << endl;
        return os;
    }
    for (int i = 0; i < list.size_; i++) {
        os << (i + 1) << ". " << *list.items_[i] << endl;
    }
    return os;
}
