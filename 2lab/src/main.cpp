#include <iostream>
#include "Note.h"
#include "NoteList.h"
#include "Exceptions.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Временная проверка классов; в следующем коммите будет заменена на меню
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    try {
        NoteList list;
        list.add(Note("Иванов", "Иван", "89211234567", 15, 3, 1999));
        list.add(Note("Петров", "Пётр", "81259876543", 2, 11, 2000));
        list.add(Note("Сидоров", "Сергей", "+79031112233", 29, 2, 2004));

        cout << "\nДо сортировки:\n" << list;
        list.sortByPhonePrefix();
        cout << "\nПосле сортировки по первым трём цифрам:\n" << list;

        int idx = list.findBySurname("Петров");
        if (idx >= 0) cout << "\nНайдено: " << list[idx] << endl;

        Note wrong("Тестов", "Тест", "12ab", 1, 1, 2000);   // вызовет исключение
    } catch (const NoteException& e) {
        cout << "\nИсключение: " << e.what() << endl;
    }
    return 0;
}
