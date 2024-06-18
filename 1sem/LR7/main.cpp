#include <iostream>
#include <stdexcept>
#include <cstdint>
#include "HexademicalNumber.h"

using namespace std;

int main() {
    try {
        cout << "First number is: ";
        HexademicalNumber num1(39060); // Пример для суммы и разности
        num1.print();

        cout << "Second number is: ";
        HexademicalNumber num2(93); // Пример для суммы и разности
        num2.print();

        cout << "Third number is: ";
        HexademicalNumber num3(-13); // Пример для возведения в степень
        num3.print();

        cout << endl;

        HexademicalNumber sum = num1 + num2;
        cout << "Result of summary in hexademical number system: ";
        sum.print();
        cout << endl;

        HexademicalNumber diff = num1 - num2;
        cout << "Result of difference in hexademical number system: ";
        diff.print();
        cout << endl;

        HexademicalNumber power = num3 ^ 3;
        cout << "Result of raising to a power in hexademical number system: ";
        power.print();
        cout << endl;

    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    return 0;
}
