#include "Keeper.h"
#include "Exceptions.h"
#include "Utils.h"
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramItem.h"
#include <fstream>
#include <cstdlib>

static const char* FILE_MARK = "CONFERENCE_KEEPER_V1";

Keeper::Keeper() : items(0), count(0), capacity(0) {
    std::cout << "[Keeper] Конструктор без параметров\n";
}
Keeper::Keeper(int cap) : items(0), count(0), capacity(0) {
    if (cap < 0) throw InvalidDataException("емкость контейнера не может быть отрицательной");
    if (cap > 0) { items = new Base*[cap]; capacity = cap; }
    std::cout << "[Keeper] Конструктор с параметром (емкость " << cap << ")\n";
}
Keeper::Keeper(const Keeper& o) : items(0), count(0), capacity(0) {
    std::cout << "[Keeper] Конструктор копирования\n";
    if (o.count > 0) {
        items = new Base*[o.count];
        capacity = o.count;
        for (int i = 0; i < o.count; i++) { items[i] = o.items[i]->clone(); count++; }
    }
}
Keeper::~Keeper() {
    std::cout << "[Keeper] Деструктор\n";
    clear();
    delete[] items;
}
Keeper& Keeper::operator=(const Keeper& o) {
    if (this != &o) {
        Keeper tmp(o);                 // копия; при исключении this не меняется
        Base** t = items; items = tmp.items; tmp.items = t;
        int c = count; count = tmp.count; tmp.count = c;
        c = capacity; capacity = tmp.capacity; tmp.capacity = c;
    }
    return *this;
}

int Keeper::getCount() const { return count; }
int Keeper::getCapacity() const { return capacity; }

void Keeper::grow() {
    int newCap = capacity == 0 ? 4 : capacity * 2;
    Base** n = new Base*[newCap];
    for (int i = 0; i < count; i++) n[i] = items[i];
    delete[] items;
    items = n;
    capacity = newCap;
}
void Keeper::add(Base* item) {
    if (!item) throw InvalidDataException("попытка добавить пустой указатель");
    if (count == capacity) grow();
    items[count++] = item;
}
void Keeper::remove(int index) {
    if (index < 0 || index >= count) throw IndexException(index, count);
    delete items[index];
    for (int i = index; i < count - 1; i++) items[i] = items[i + 1];
    count--;
}
void Keeper::clear() {
    for (int i = 0; i < count; i++) delete items[i];
    count = 0;
}
Base& Keeper::operator[](int index) {
    if (index < 0 || index >= count) throw IndexException(index, count);
    return *items[index];
}
const Base& Keeper::operator[](int index) const {
    if (index < 0 || index >= count) throw IndexException(index, count);
    return *items[index];
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream f(filename.c_str());
    if (!f) throw FileException("не удалось открыть \"" + filename + "\" для записи");
    f << FILE_MARK << "\n" << count << "\n";
    for (int i = 0; i < count; i++) {
        f << items[i]->typeName() << "\n";
        items[i]->save(f);
    }
    f.flush();
    if (!f) throw FileException("ошибка записи в \"" + filename + "\"");
}

static Base* createByName(const std::string& name) {
    if (name == "Speaker") return new Speaker();
    if (name == "Administrator") return new Administrator();
    if (name == "ProgramItem") return new ProgramItem();
    throw FormatException("неизвестный тип объекта \"" + name + "\"");
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream f(filename.c_str());
    if (!f) throw FileException("не удалось открыть \"" + filename + "\" для чтения");
    if (readField(f) != FILE_MARK) throw FormatException("отсутствует заголовок " + std::string(FILE_MARK));
    std::string cs = readField(f);
    char* end = 0;
    long n = std::strtol(cs.c_str(), &end, 10);
    if (cs.empty() || *end != '\0' || n < 0) throw FormatException("некорректное количество объектов");

    Keeper tmp;                         // загружаем во временный контейнер
    for (long i = 0; i < n; i++) {
        Base* b = createByName(readField(f));
        try {
            b->load(f);
        } catch (...) {
            delete b;
            throw;
        }
        tmp.add(b);
    }
    // успех: забираем содержимое tmp
    clear();
    delete[] items;
    items = tmp.items; count = tmp.count; capacity = tmp.capacity;
    tmp.items = 0; tmp.count = 0; tmp.capacity = 0;
}

std::ostream& operator<<(std::ostream& os, const Keeper& k) {
    if (k.count == 0) os << "(контейнер пуст)\n";
    for (int i = 0; i < k.count; i++)
        os << "#" << i + 1 << " " << *k.items[i] << "\n";
    return os;
}
