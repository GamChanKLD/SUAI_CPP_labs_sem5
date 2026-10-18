#include <iostream>
#include "Keeper.h"
#include "Speaker.h"
#include "Administrator.h"
#include "ProgramItem.h"
#include "Exceptions.h"
#include "Utils.h"
#ifdef _WIN32
#include <windows.h>
#endif

static void addItem(Keeper& k) {
    std::cout << "\nЧто добавить?\n1 - Выступающий\n2 - Администрация\n3 - Элемент программы\n0 - Отмена\n";
    int c = inputInt("Выбор: ", 0, 3);
    Base* b = 0;
    if (c == 1) {
        std::string n = inputLine("ФИО: "), o = inputLine("Организация/ВУЗ: ");
        std::string t = inputLine("Доклад: "), a = inputLine("Аннотация доклада: ");
        b = new Speaker(n, o, t, a);
    } else if (c == 2) {
        std::string n = inputLine("ФИО: "), p = inputLine("Должность: ");
        std::string r = inputLine("Область ответственности: ");
        b = new Administrator(n, p, r);
    } else if (c == 3) {
        int d = inputInt("День (1-31): ", 1, 31);
        std::string t = inputLine("Время (ЧЧ:ММ): ");
        std::string ti = inputLine("Наименование: ");
        b = new ProgramItem(d, t, ti);
    }
    if (b) {
        try { k.add(b); } catch (...) { delete b; throw; }
        std::cout << "Объект добавлен.\n";
    }
}

static void removeItem(Keeper& k) {
    if (k.getCount() == 0) { std::cout << "Контейнер пуст.\n"; return; }
    std::cout << k;
    k.remove(inputInt("Номер удаляемого элемента: ", 1, 1000000) - 1);
    std::cout << "Объект удален.\n";
}

static void editItem(Keeper& k) {
    if (k.getCount() == 0) { std::cout << "Контейнер пуст.\n"; return; }
    std::cout << k;
    int i = inputInt("Номер изменяемого элемента: ", 1, 1000000) - 1;
    k[i].edit();
    std::cout << "Готово.\n";
}

static void copyDemo(const Keeper& k) {
    std::cout << "\n--- Копирование контейнера (конструктор копирования) ---\n";
    Keeper copy(k);
    std::cout << "Копия содержит элементов: " << copy.getCount() << "\n" << copy;
    std::cout << "--- Конец копии, сейчас будет вызван деструктор ---\n";
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif
    Keeper keeper;
    bool run = true;
    while (run) {
        try {
            std::cout << "\n===== Конференция (элементов: " << keeper.getCount() << ") =====\n"
                      << "1 - Добавить элемент\n2 - Удалить элемент\n3 - Показать все\n"
                      << "4 - Изменить элемент\n5 - Сохранить в файл\n6 - Загрузить из файла\n"
                      << "7 - Демонстрация копирования контейнера\n0 - Выход\n";
            switch (inputInt("Выбор: ", 0, 7)) {
                case 1: addItem(keeper); break;
                case 2: removeItem(keeper); break;
                case 3: std::cout << keeper; break;
                case 4: editItem(keeper); break;
                case 5: {
                    std::string f = inputLine("Имя файла: ");
                    keeper.saveToFile(f);
                    std::cout << "Сохранено.\n";
                    break;
                }
                case 6: {
                    std::string f = inputLine("Имя файла: ");
                    keeper.loadFromFile(f);
                    std::cout << "Загружено элементов: " << keeper.getCount() << "\n";
                    break;
                }
                case 7: copyDemo(keeper); break;
                case 0: run = false; break;
            }
        } catch (const ConferenceException& e) {
            std::cout << "\n!!! " << e.what() << "\n";
            if (std::cin.eof()) run = false;
        } catch (const std::exception& e) {
            std::cout << "\n!!! Системная ошибка: " << e.what() << "\n";
        }
    }
    std::cout << "Завершение работы...\n";
    return 0;
}
