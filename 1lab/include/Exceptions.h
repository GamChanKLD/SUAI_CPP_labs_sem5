#pragma once
#include <exception>
#include <string>

// Базовое исключение программы
class ConferenceException : public std::exception {
protected:
    std::string message;
public:
    explicit ConferenceException(const std::string& msg);
    virtual ~ConferenceException() throw();
    virtual const char* what() const throw();
};

// Индекс вне диапазона контейнера
class IndexException : public ConferenceException {
public:
    IndexException(int index, int size);
};

// Некорректное значение поля
class InvalidDataException : public ConferenceException {
public:
    explicit InvalidDataException(const std::string& msg);
};

// Ошибка открытия/записи файла
class FileException : public ConferenceException {
public:
    explicit FileException(const std::string& msg);
};

// Файл имеет неверный формат
class FormatException : public ConferenceException {
public:
    explicit FormatException(const std::string& msg);
};
