#include "Exceptions.h"
#include <sstream>

ConferenceException::ConferenceException(const std::string& msg) : message(msg) {}
ConferenceException::~ConferenceException() throw() {}
const char* ConferenceException::what() const throw() { return message.c_str(); }

IndexException::IndexException(int index, int size)
    : ConferenceException("") {
    std::ostringstream os;
    os << "Ошибка индекса: элемент №" << index + 1 << " не существует (в контейнере элементов: " << size << ")";
    message = os.str();
}
InvalidDataException::InvalidDataException(const std::string& msg)
    : ConferenceException("Некорректные данные: " + msg) {}
FileException::FileException(const std::string& msg)
    : ConferenceException("Ошибка файла: " + msg) {}
FormatException::FormatException(const std::string& msg)
    : ConferenceException("Неверный формат файла: " + msg) {}
