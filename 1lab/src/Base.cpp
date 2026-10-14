#include "Base.h"

Base::Base() { std::cout << "  [Base] Конструктор без параметров\n"; }
Base::Base(const Base&) { std::cout << "  [Base] Конструктор копирования\n"; }
Base::~Base() { std::cout << "  [Base] Деструктор\n"; }
Base& Base::operator=(const Base&) { return *this; }

std::ostream& operator<<(std::ostream& os, const Base& b) {
    b.print(os);
    return os;
}
