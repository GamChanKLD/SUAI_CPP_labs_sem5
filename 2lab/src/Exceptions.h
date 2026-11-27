#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Базовое исключение программы: хранит текст, поясняющий ошибку
class NoteException : public std::exception {
protected:
    std::string message_;
public:
    explicit NoteException(const std::string& message);
    virtual ~NoteException() noexcept;
    const char* what() const noexcept override;
};

// Некорректная дата рождения
class InvalidDateException : public NoteException {
public:
    InvalidDateException(int day, int month, int year);
};

// Некорректный номер телефона
class InvalidPhoneException : public NoteException {
public:
    explicit InvalidPhoneException(const std::string& phone);
};

// Пустое текстовое поле (фамилия или имя)
class EmptyFieldException : public NoteException {
public:
    explicit EmptyFieldException(const std::string& fieldName);
};

// Индекс вне границ списка
class IndexOutOfRangeException : public NoteException {
public:
    IndexOutOfRangeException(int index, int size);
};

// Операция над пустым списком
class EmptyListException : public NoteException {
public:
    EmptyListException();
};

// Ошибка ввода (например, вместо числа введены буквы)
class InvalidInputException : public NoteException {
public:
    explicit InvalidInputException(const std::string& details);
};

#endif
