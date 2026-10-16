#include "ProgramItem.h"
#include "Exceptions.h"
#include "Utils.h"
#include <cstdlib>

ProgramItem::ProgramItem() : day(1), time("00:00") {
    std::cout << "  [ProgramItem] Конструктор без параметров\n";
}
ProgramItem::ProgramItem(int d, const std::string& t, const std::string& ti) : day(1), time("00:00") {
    setDay(d); setTime(t); setTitle(ti);
    std::cout << "  [ProgramItem] Конструктор с параметрами\n";
}
ProgramItem::ProgramItem(const ProgramItem& p)
    : Base(p), day(p.day), time(p.time), title(p.title) {
    std::cout << "  [ProgramItem] Конструктор копирования\n";
}
ProgramItem::~ProgramItem() { std::cout << "  [ProgramItem] Деструктор (" << title << ")\n"; }

ProgramItem& ProgramItem::operator=(const ProgramItem& p) {
    if (this != &p) { Base::operator=(p); day = p.day; time = p.time; title = p.title; }
    return *this;
}
bool ProgramItem::operator==(const ProgramItem& p) const {
    return day == p.day && time == p.time && title == p.title;
}
bool ProgramItem::operator<(const ProgramItem& p) const {
    return day < p.day || (day == p.day && time < p.time);
}

int ProgramItem::getDay() const { return day; }
const std::string& ProgramItem::getTime() const { return time; }
const std::string& ProgramItem::getTitle() const { return title; }

void ProgramItem::setDay(int v) {
    if (v < 1 || v > 31) throw InvalidDataException("день конференции должен быть от 1 до 31");
    day = v;
}
void ProgramItem::setTime(const std::string& v) {
    bool ok = v.size() == 5 && v[2] == ':';
    for (int i = 0; ok && i < 5; i++)
        if (i != 2 && (v[i] < '0' || v[i] > '9')) ok = false;
    if (ok) {
        int h = (v[0] - '0') * 10 + (v[1] - '0');
        int m = (v[3] - '0') * 10 + (v[4] - '0');
        ok = h < 24 && m < 60;
    }
    if (!ok) throw InvalidDataException("время должно быть в формате ЧЧ:ММ (например, 09:30)");
    time = v;
}
void ProgramItem::setTitle(const std::string& v) {
    if (v.empty()) throw InvalidDataException("поле \"Наименование\" не может быть пустым");
    title = v;
}

void ProgramItem::print(std::ostream& os) const {
    os << "[Программа] День: " << day << "\n"
       << "            Время: " << time << "\n"
       << "            Наименование: " << title;
}
void ProgramItem::save(std::ostream& os) const {
    os << day << "\n" << time << "\n" << title << "\n";
}
void ProgramItem::load(std::istream& is) {
    std::string d = readField(is), t = readField(is), ti = readField(is);
    char* end = 0;
    long v = std::strtol(d.c_str(), &end, 10);
    if (d.empty() || *end != '\0') throw FormatException("день программы не является числом");
    setDay((int)v); setTime(t); setTitle(ti);
}
void ProgramItem::edit() {
    std::cout << "1 - День\n2 - Время\n3 - Наименование\n0 - Отмена\n";
    int c = inputInt("Что изменить: ", 0, 3);
    switch (c) {
        case 1: setDay(inputInt("Новый день (1-31): ", 1, 31)); break;
        case 2: setTime(inputLine("Новое время (ЧЧ:ММ): ")); break;
        case 3: setTitle(inputLine("Новое наименование: ")); break;
    }
}
Base* ProgramItem::clone() const { return new ProgramItem(*this); }
std::string ProgramItem::typeName() const { return "ProgramItem"; }
