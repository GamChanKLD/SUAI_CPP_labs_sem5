// Промежуточная версия main: проверка утилит ввода и исключений.
// На следующих этапах будет заменена полным меню.
#include <iostream>
#include "Exceptions.h"
#include "Utils.h"
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    try {
        std::string name = inputLine("Введите строку: ");
        std::cout << "Вы ввели: " << name << "\n";

        int n = inputInt("Введите число от 1 до 10: ", 1, 10);
        std::cout << "Число: " << n << "\n";

        throw IndexException(n, 3);   // проверка исключения
    } catch (const ConferenceException& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }
    return 0;
}