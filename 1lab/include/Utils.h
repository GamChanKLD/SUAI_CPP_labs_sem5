#pragma once
#include <iostream>
#include <string>

// Ввод строки с клавиатуры с приглашением
std::string inputLine(const std::string& prompt);
// Ввод целого числа в диапазоне [min, max] (повторяет запрос при ошибке)
int inputInt(const std::string& prompt, int min, int max);
// Чтение одной строки-поля из файла (бросает FormatException)
std::string readField(std::istream& in);
