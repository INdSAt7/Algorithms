//
// Created by agoru on 11.06.2024.
//

#ifndef LR7_HEXADEMICALNUMBER_H
#define LR7_HEXADEMICALNUMBER_H

#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <cmath>

using namespace std;

class HexademicalNumber {
private:
    uint8_t high;  // Старший байт
    uint8_t mid;   // Средний байт
    uint8_t low;   // Младший байт

    // Функция для получения значения разряда в шестиричной системе
    int getDigit(int position) const {
        if (position < 0 || position > 6) {
            throw out_of_range("Position out of range");
        }
        int shift = position * 3;
        int value = 0;

        if (shift < 8) {
            if (shift + 2 > 7) {
                int lowBits = (low >> shift) & ((1 << (8 - shift)) - 1);
                int midBits = (mid & ((1 << (shift + 3 - 8)) - 1)) << (8 - shift);
                value = lowBits | midBits;
            } else {
                value = (low >> shift) & 0x7;
            }
        } else if (shift < 16) {
            shift -= 8;
            if (shift + 2 > 7) {
                int midBits = (mid >> shift) & ((1 << (8 - shift)) - 1);
                int highBits = (high & ((1 << (shift + 3 - 8)) - 1)) << (8 - shift);
                value = midBits | highBits;
            } else {
                value = (mid >> shift) & 0x7;
            }
        } else {
            shift -= 16;
            value = (high >> shift) & 0x7;
        }

        return value;
    }

    // Функция для установки значения разряда в шестиричной системе
    void setDigit(int position, int value) {
        if (position < 0 || position > 6) {
            throw out_of_range("Position out of range");
        }
        if (value < 0 || value > 5) {
            throw invalid_argument("Invalid digit value");
        }

        int shift = position * 3;

        if (shift < 8) {
            if (shift + 2 > 7) {
                low &= ~(((1 << (8 - shift)) - 1) << shift);  // Очищаем нужные биты в младшем байте
                low |= (value & ((1 << (8 - shift)) - 1)) << shift;  // Устанавливаем новые биты в младшем байте

                mid &= ~((1 << (shift + 3 - 8)) - 1);  // Очищаем нужные биты в среднем байте
                mid |= (value >> (8 - shift)) & ((1 << (shift + 3 - 8)) - 1);  // Устанавливаем новые биты в среднем байте
            } else {
                low &= ~(0x7 << shift);  // Очищаем нужные биты
                low |= (value & 0x7) << shift;  // Устанавливаем новые биты
            }
        } else if (shift < 16) {
            shift -= 8;
            if (shift + 2 > 7) {
                mid &= ~(((1 << (8 - shift)) - 1) << shift);  // Очищаем нужные биты в среднем байте
                mid |= (value & ((1 << (8 - shift)) - 1)) << shift;  // Устанавливаем новые биты в среднем байте

                high &= ~((1 << (shift + 3 - 8)) - 1);  // Очищаем нужные биты в старшем байте
                high |= (value >> (8 - shift)) & ((1 << (shift + 3 - 8)) - 1);  // Устанавливаем новые биты в старшем байте
            } else {
                mid &= ~(0x7 << shift);  // Очищаем нужные биты в среднем байте
                mid |= (value & 0x7) << shift;  // Устанавливаем новые биты в среднем байте
            }
        } else {
            shift -= 16;
            high &= ~(0x7 << shift);  // Очищаем нужные биты в старшем байте
            high |= (value & 0x7) << shift;  // Устанавливаем новые биты в старшем байте
        }
    }

    // Функция для получения знака числа
    bool getSign() const {
        return (high >> 7) & 0x1;
    }

    // Функция для установки знака числа
    void setSign(bool sign) {
        if (sign) {
            high |= (1 << 7);
        } else {
            high &= ~(1 << 7);
        }
    }

public:
    // Конструктор по умолчанию
    HexademicalNumber() : high(0), mid(0), low(0) {}

    // Конструктор из целого числа
    HexademicalNumber(int value) : high(0), mid(0), low(0) {
        if (value < -279935 || value > 279935) {  // Значения от -279935 до 279935 включительно
            cerr << "Value: " << value << " out of range for septenary system" << endl;
            throw out_of_range("Value out of range for septenary system");
        }
        setSign(value < 0);
        value = abs(value);
        for (int i = 0; i < 7; ++i) {
            setDigit(i, value % 6);
            value = value / 6;
        }
    }

    // Функция для вывода числа в шестиричной системе счисления
    void print() const {
        cout << (getSign() ? "-" : "+");
        for (int i = 6; i >= 0; --i) {
            cout << getDigit(i);
        }
        cout << endl;
    }

    // Преобразование к целому числу
    int toInt() const {
        int value = 0;
        for (int i = 6; i >= 0; --i) {
            value = value * 6 + getDigit(i);
        }
        return getSign() ? -value : value;
    }

    // Операция сложения
    HexademicalNumber operator+(const HexademicalNumber& other) const {
        int thisValue = this->toInt();
        int otherValue = other.toInt();
        int resultValue = thisValue + otherValue;
        return HexademicalNumber(resultValue);
    }

    // Операция вычитания
    HexademicalNumber operator-(const HexademicalNumber& other) const {
        int thisValue = this->toInt();
        int otherValue = other.toInt();
        int resultValue = thisValue - otherValue;
        return HexademicalNumber(resultValue);
    }

    // Операция возведения в степень
    HexademicalNumber operator^(int exponent) const {
        if (exponent < 0) {
            throw invalid_argument("Negative exponent not supported");
        }
        int baseValue = this->toInt();
        int resultValue = pow(baseValue, exponent);
        return HexademicalNumber(resultValue);
    }

    // Операция умножения
    HexademicalNumber operator*(const HexademicalNumber& other) const {
        int thisValue = this->toInt();
        int otherValue = other.toInt();
        int resultValue = thisValue * otherValue;
        return HexademicalNumber(resultValue);
    }
};


#endif //LR7_HEXADEMICALNUMBER_H
