//
// Created by agoru on 11.06.2024.
//

#ifndef RK3_STACK_H
#define RK3_STACK_H

#include "iostream"
#include <vector>
#include "node.h"

using namespace std;

class stack {
private:
    Node **values;
    unsigned int currentSize;
    int capacity;

public:
    bool push(Node *value) {
        if (isFull()) {
            cout << "Нельзя добавить значение в стек: он полон" << endl;
            return false;
        }

        values[currentSize] = value;
        currentSize++;

        return true;
    }

    bool pop(Node *&value) {
        if (isEmpty()) {
            cout << "Нельзя взять значение из стека: он пуст" << endl;
            return false;
        }

        currentSize--;

        value = values[currentSize];

        return true;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == capacity;
    }

    Node *getTopElement() {
        return values[currentSize - 1];
    }

    void display() {
        cout << "Текущие значения в стеке:" << endl;

        for (int i = 0; i < currentSize; ++i) {
            cout << values[i] << " ";
        }

        cout << endl;
    }

    void free() {
        delete values;
    }

    stack(const int cap) {
        values = new Node *[cap];
        capacity = cap;
        currentSize = 0;
    }
};

#endif //RK3_STACK_H
