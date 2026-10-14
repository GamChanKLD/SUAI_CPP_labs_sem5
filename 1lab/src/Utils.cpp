#include "Utils.h"
#include "Exceptions.h"
#include <cstdlib>

std::string inputLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    if (!std::getline(std::cin, s))
        throw ConferenceException("Ввод прерван (конец потока ввода)");
    if (!s.empty() && s[s.size() - 1] == '\r') s.erase(s.size() - 1);
    return s;
}

int inputInt(const std::string& prompt, int min, int max) {
    while (true) {
        std::string s = inputLine(prompt);
        char* end = 0;
        long v = std::strtol(s.c_str(), &end, 10);
        if (!s.empty() && *end == '\0' && v >= min && v <= max)
            return (int)v;
        std::cout << "Введите целое число от " << min << " до " << max << ".\n";
    }
}

std::string readField(std::istream& in) {
    std::string s;
    if (!std::getline(in, s))
        throw FormatException("неожиданный конец файла");
    if (!s.empty() && s[s.size() - 1] == '\r') s.erase(s.size() - 1);
    return s;
}
