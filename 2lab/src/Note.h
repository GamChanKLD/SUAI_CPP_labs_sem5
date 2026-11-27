#ifndef NOTE_H
#define NOTE_H

#include <iostream>
#include <string>

// Запись телефонной книги: фамилия, имя, телефон, день рождения (день, месяц, год)
class Note {
private:
    std::string surname_;
    std::string name_;
    std::string phone_;
    int* birthday_;   // динамический массив из трёх чисел: [0] день, [1] месяц, [2] год

public:
    // Конструкторы и деструктор (каждый вызов сопровождается сообщением)
    Note();
    Note(const std::string& surname, const std::string& name, const std::string& phone,
         int day, int month, int year);
    Note(const Note& other);
    ~Note();

    // Перегруженные операции
    Note& operator=(const Note& other);
    bool operator<(const Note& other) const;   // сравнение по первым трём цифрам телефона

    // Методы просмотра (get)
    const std::string& getSurname() const;
    const std::string& getName() const;
    const std::string& getPhone() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    int getPhonePrefix() const;   // число из первых трёх цифр номера (для сортировки)

    // Методы установки (set), с проверкой корректности
    void setSurname(const std::string& surname);
    void setName(const std::string& name);
    void setPhone(const std::string& phone);
    void setBirthday(int day, int month, int year);

    // Проверки (бросают исключения при ошибке)
    static void validateDate(int day, int month, int year);
    static void validatePhone(const std::string& phone);

    // Перегруженные операции извлечения и вставки
    friend std::ostream& operator<<(std::ostream& os, const Note& note);
    friend std::istream& operator>>(std::istream& is, Note& note);
};

#endif
