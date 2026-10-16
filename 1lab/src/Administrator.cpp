#include "Administrator.h"
#include "Exceptions.h"
#include "Utils.h"

static void check(const std::string& v, const char* field) {
    if (v.empty()) throw InvalidDataException(std::string("поле \"") + field + "\" не может быть пустым");
}

Administrator::Administrator() { std::cout << "  [Administrator] Конструктор без параметров\n"; }
Administrator::Administrator(const std::string& n, const std::string& p, const std::string& r) {
    setFullName(n); setPosition(p); setResponsibility(r);
    std::cout << "  [Administrator] Конструктор с параметрами\n";
}
Administrator::Administrator(const Administrator& a)
    : Base(a), fullName(a.fullName), position(a.position), responsibility(a.responsibility) {
    std::cout << "  [Administrator] Конструктор копирования\n";
}
Administrator::~Administrator() { std::cout << "  [Administrator] Деструктор (" << fullName << ")\n"; }

Administrator& Administrator::operator=(const Administrator& a) {
    if (this != &a) {
        Base::operator=(a);
        fullName = a.fullName; position = a.position; responsibility = a.responsibility;
    }
    return *this;
}
bool Administrator::operator==(const Administrator& a) const {
    return fullName == a.fullName && position == a.position && responsibility == a.responsibility;
}

const std::string& Administrator::getFullName() const { return fullName; }
const std::string& Administrator::getPosition() const { return position; }
const std::string& Administrator::getResponsibility() const { return responsibility; }
void Administrator::setFullName(const std::string& v) { check(v, "ФИО"); fullName = v; }
void Administrator::setPosition(const std::string& v) { check(v, "Должность"); position = v; }
void Administrator::setResponsibility(const std::string& v) { check(v, "Область ответственности"); responsibility = v; }

void Administrator::print(std::ostream& os) const {
    os << "[Администрация] ФИО: " << fullName << "\n"
       << "                Должность: " << position << "\n"
       << "                Область ответственности: " << responsibility;
}
void Administrator::save(std::ostream& os) const {
    os << fullName << "\n" << position << "\n" << responsibility << "\n";
}
void Administrator::load(std::istream& is) {
    std::string n = readField(is), p = readField(is), r = readField(is);
    setFullName(n); setPosition(p); setResponsibility(r);
}
void Administrator::edit() {
    std::cout << "1 - ФИО\n2 - Должность\n3 - Область ответственности\n0 - Отмена\n";
    int c = inputInt("Что изменить: ", 0, 3);
    switch (c) {
        case 1: setFullName(inputLine("Новое ФИО: ")); break;
        case 2: setPosition(inputLine("Новая должность: ")); break;
        case 3: setResponsibility(inputLine("Новая область ответственности: ")); break;
    }
}
Base* Administrator::clone() const { return new Administrator(*this); }
std::string Administrator::typeName() const { return "Administrator"; }
