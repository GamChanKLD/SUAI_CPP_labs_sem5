// Промежуточная версия main: проверка классов-наследников.
// На следующем этапе будет заменена полным меню с контейнером Keeper.
#include <iostream>
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramItem.h"
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
        std::cout << "--- Создание объектов ---\n";
        std::string n = inputLine("Выступающий, ФИО: ");
        std::string o = inputLine("Организация/ВУЗ: ");
        std::string t = inputLine("Доклад: ");
        std::string a = inputLine("Аннотация: ");
        Speaker speaker(n, o, t, a);

        Administrator admin("Петрова А.А.", "Директор", "Организация конференции");
        ProgramItem item(1, "09:30", "Открытие конференции");

        std::cout << "\n--- Полиморфизм: работа через указатель на Base ---\n";
        Base* objects[3] = { &speaker, &admin, &item };
        for (int i = 0; i < 3; i++)
            std::cout << *objects[i] << "\n";

        std::cout << "\n--- Копирование (clone) ---\n";
        Base* copy = speaker.clone();
        std::cout << *copy << "\n";
        delete copy;

        std::cout << "\n--- Проверка исключения в сеттере ---\n";
        item.setTime("25:99");   // неверное время
    } catch (const ConferenceException& e) {
        std::cout << "Исключение: " << e.what() << "\n";
    }
    std::cout << "\n--- Конец программы, вызываются деструкторы ---\n";
    return 0;
}
