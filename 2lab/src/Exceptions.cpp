#include "Exceptions.h"

NoteException::NoteException(const std::string& message) : message_(message) {}

NoteException::~NoteException() noexcept {}

const char* NoteException::what() const noexcept {
    return message_.c_str();
}

InvalidDateException::InvalidDateException(int day, int month, int year)
    : NoteException("Некорректная дата рождения: " + std::to_string(day) + "." +
                    std::to_string(month) + "." + std::to_string(year) +
                    " (год 1900-2100, месяц 1-12, день по календарю)") {}

InvalidPhoneException::InvalidPhoneException(const std::string& phone)
    : NoteException("Некорректный номер телефона: \"" + phone +
                    "\" (допустимо от 3 до 15 цифр, в начале может стоять '+')") {}

EmptyFieldException::EmptyFieldException(const std::string& fieldName)
    : NoteException("Поле \"" + fieldName + "\" не может быть пустым") {}

IndexOutOfRangeException::IndexOutOfRangeException(int index, int size)
    : NoteException("Индекс " + std::to_string(index) + " вне границ списка (размер списка: " +
                    std::to_string(size) + ")") {}

EmptyListException::EmptyListException()
    : NoteException("Операция невозможна: список записей пуст") {}

InvalidInputException::InvalidInputException(const std::string& details)
    : NoteException("Ошибка ввода: " + details) {}
