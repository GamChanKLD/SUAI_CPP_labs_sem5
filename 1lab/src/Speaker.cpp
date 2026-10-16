#include "Speaker.h"
#include "Exceptions.h"
#include "Utils.h"

static void check(const std::string& v, const char* field) {
    if (v.empty()) throw InvalidDataException(std::string("поле \"") + field + "\" не может быть пустым");
}

Speaker::Speaker() { std::cout << "  [Speaker] Конструктор без параметров\n"; }
Speaker::Speaker(const std::string& n, const std::string& o, const std::string& t, const std::string& a) {
    setFullName(n); setOrganization(o); setTopic(t); setAnnotation(a);
    std::cout << "  [Speaker] Конструктор с параметрами\n";
}
Speaker::Speaker(const Speaker& s)
    : Base(s), fullName(s.fullName), organization(s.organization), topic(s.topic), annotation(s.annotation) {
    std::cout << "  [Speaker] Конструктор копирования\n";
}
Speaker::~Speaker() { std::cout << "  [Speaker] Деструктор (" << fullName << ")\n"; }

Speaker& Speaker::operator=(const Speaker& s) {
    if (this != &s) {
        Base::operator=(s);
        fullName = s.fullName; organization = s.organization;
        topic = s.topic; annotation = s.annotation;
    }
    return *this;
}
bool Speaker::operator==(const Speaker& s) const {
    return fullName == s.fullName && organization == s.organization &&
           topic == s.topic && annotation == s.annotation;
}

const std::string& Speaker::getFullName() const { return fullName; }
const std::string& Speaker::getOrganization() const { return organization; }
const std::string& Speaker::getTopic() const { return topic; }
const std::string& Speaker::getAnnotation() const { return annotation; }
void Speaker::setFullName(const std::string& v) { check(v, "ФИО"); fullName = v; }
void Speaker::setOrganization(const std::string& v) { check(v, "Организация/ВУЗ"); organization = v; }
void Speaker::setTopic(const std::string& v) { check(v, "Доклад"); topic = v; }
void Speaker::setAnnotation(const std::string& v) { check(v, "Аннотация"); annotation = v; }

void Speaker::print(std::ostream& os) const {
    os << "[Выступающий] ФИО: " << fullName << "\n"
       << "              Организация/ВУЗ: " << organization << "\n"
       << "              Доклад: " << topic << "\n"
       << "              Аннотация: " << annotation;
}
void Speaker::save(std::ostream& os) const {
    os << fullName << "\n" << organization << "\n" << topic << "\n" << annotation << "\n";
}
void Speaker::load(std::istream& is) {
    std::string n = readField(is), o = readField(is), t = readField(is), a = readField(is);
    setFullName(n); setOrganization(o); setTopic(t); setAnnotation(a);
}
void Speaker::edit() {
    std::cout << "1 - ФИО\n2 - Организация/ВУЗ\n3 - Доклад\n4 - Аннотация\n0 - Отмена\n";
    int c = inputInt("Что изменить: ", 0, 4);
    switch (c) {
        case 1: setFullName(inputLine("Новое ФИО: ")); break;
        case 2: setOrganization(inputLine("Новая организация/ВУЗ: ")); break;
        case 3: setTopic(inputLine("Новый доклад: ")); break;
        case 4: setAnnotation(inputLine("Новая аннотация: ")); break;
    }
}
Base* Speaker::clone() const { return new Speaker(*this); }
std::string Speaker::typeName() const { return "Speaker"; }
