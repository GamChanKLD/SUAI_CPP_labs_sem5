#include "Note.h"
#include "Exceptions.h"
#include <cctype>
#include <limits>

using namespace std;

namespace {
    bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    }

    int daysInMonth(int month, int year) {
        static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year)) return 29;
        return days[month - 1];
    }

    // Сбрасывает состояние потока после ошибки и бросает исключение
    void failInput(istream& is, const string& details) {
        is.clear();
        is.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException(details);
    }
}

// ---------- Конструкторы и деструктор ----------

Note::Note() : surname_("Неизвестно"), name_("Неизвестно"), phone_("000"), birthday_(nullptr) {
    birthday_ = new int[3];
    birthday_[0] = 1;
    birthday_[1] = 1;
    birthday_[2] = 2000;
    cout << "[NOTE] Вызван конструктор без параметров (объект: " << surname_ << " " << name_ << ")" << endl;
}

Note::Note(const string& surname, const string& name, const string& phone,
           int day, int month, int year) : birthday_(nullptr) {
    // Сначала все проверки, и только потом выделение памяти (чтобы не было утечки при исключении)
    setSurname(surname);
    setName(name);
    validatePhone(phone);
    validateDate(day, month, year);
    phone_ = phone;
    birthday_ = new int[3];
    birthday_[0] = day;
    birthday_[1] = month;
    birthday_[2] = year;
    cout << "[NOTE] Вызван конструктор с параметрами (объект: " << surname_ << " " << name_ << ")" << endl;
}

Note::Note(const Note& other)
    : surname_(other.surname_), name_(other.name_), phone_(other.phone_), birthday_(nullptr) {
    birthday_ = new int[3];
    for (int i = 0; i < 3; i++) birthday_[i] = other.birthday_[i];
    cout << "[NOTE] Вызван конструктор копирования (объект: " << surname_ << " " << name_ << ")" << endl;
}

Note::~Note() {
    cout << "[NOTE] Вызван деструктор (объект: " << surname_ << " " << name_ << ")" << endl;
    delete[] birthday_;
}

// ---------- Операции ----------

Note& Note::operator=(const Note& other) {
    if (this != &other) {
        surname_ = other.surname_;
        name_ = other.name_;
        phone_ = other.phone_;
        for (int i = 0; i < 3; i++) birthday_[i] = other.birthday_[i];
    }
    return *this;
}

bool Note::operator<(const Note& other) const {
    return getPhonePrefix() < other.getPhonePrefix();
}

// ---------- get ----------

const string& Note::getSurname() const { return surname_; }
const string& Note::getName() const { return name_; }
const string& Note::getPhone() const { return phone_; }
int Note::getDay() const { return birthday_[0]; }
int Note::getMonth() const { return birthday_[1]; }
int Note::getYear() const { return birthday_[2]; }

int Note::getPhonePrefix() const {
    int result = 0;
    int count = 0;
    for (size_t i = 0; i < phone_.size() && count < 3; i++) {
        if (isdigit(static_cast<unsigned char>(phone_[i]))) {
            result = result * 10 + (phone_[i] - '0');
            count++;
        }
    }
    return result;
}

// ---------- set ----------

void Note::setSurname(const string& surname) {
    if (surname.empty()) throw EmptyFieldException("Фамилия");
    surname_ = surname;
}

void Note::setName(const string& name) {
    if (name.empty()) throw EmptyFieldException("Имя");
    name_ = name;
}

void Note::setPhone(const string& phone) {
    validatePhone(phone);
    phone_ = phone;
}

void Note::setBirthday(int day, int month, int year) {
    validateDate(day, month, year);
    birthday_[0] = day;
    birthday_[1] = month;
    birthday_[2] = year;
}

// ---------- Проверки ----------

void Note::validateDate(int day, int month, int year) {
    if (year < 1900 || year > 2100 || month < 1 || month > 12 ||
        day < 1 || day > daysInMonth(month, year)) {
        throw InvalidDateException(day, month, year);
    }
}

void Note::validatePhone(const string& phone) {
    size_t start = (!phone.empty() && phone[0] == '+') ? 1 : 0;
    size_t digits = phone.size() - start;
    if (digits < 3 || digits > 15) throw InvalidPhoneException(phone);
    for (size_t i = start; i < phone.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(phone[i]))) throw InvalidPhoneException(phone);
    }
}

// ---------- Ввод / вывод ----------

ostream& operator<<(ostream& os, const Note& note) {
    os << note.surname_ << " " << note.name_ << " | тел.: " << note.phone_ << " | д.р.: ";
    os << (note.birthday_[0] < 10 ? "0" : "") << note.birthday_[0] << ".";
    os << (note.birthday_[1] < 10 ? "0" : "") << note.birthday_[1] << ".";
    os << note.birthday_[2];
    return os;
}

istream& operator>>(istream& is, Note& note) {
    bool console = (&is == &cin);   // подсказки выводим только при вводе с клавиатуры
    string surname, name, phone;
    int day, month, year;

    if (console) cout << "Фамилия: ";
    if (!(is >> surname)) failInput(is, "не удалось считать фамилию");

    if (console) cout << "Имя: ";
    if (!(is >> name)) failInput(is, "не удалось считать имя");

    if (console) cout << "Номер телефона: ";
    if (!(is >> phone)) failInput(is, "не удалось считать номер телефона");

    if (console) cout << "День рождения (день месяц год через пробел): ";
    if (!(is >> day >> month >> year)) failInput(is, "дата рождения должна состоять из трёх чисел");

    // Сначала проверяем все данные, и только потом изменяем объект
    Note::validatePhone(phone);
    Note::validateDate(day, month, year);
    note.setSurname(surname);
    note.setName(name);
    note.setPhone(phone);
    note.setBirthday(day, month, year);
    return is;
}
