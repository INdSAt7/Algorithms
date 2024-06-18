//
// Created by agoru on 11.06.2024.
//

#ifndef RK3_QUEUE_H
#define RK3_QUEUE_H

#include "iostream"

using namespace std;

class queue {
private:
    int *items;
    int front, back,
            capacity;

public:
    queue(const int cap) {
        front = -1;
        back = -1;
        capacity = cap;
        items = new int[cap];
    }

    bool isFull() {
        if (front == 0 && back == capacity - 1) {
            return true;
        }

        if (front == back + 1) {
            return true;
        }

        return false;
    }

    bool isEmpty() {
        if (front == -1)
            return true;
        else
            return false;
    }

    bool push(int element) {
        if (isFull()) {
            cout << "Очередь заполнена";
            return false;
        } else {
            if (front == -1) {
                front = 0;
            }
            back = (back + 1) % capacity;
            items[back] = element;
            return true;
        }
    }

    bool pop(int &value) {
        if (isEmpty()) {
            cout << "Очередь пуста" << endl;
            return false;
        } else {
            value = items[front];
            if (front == back) {
                front = -1;
                back = -1;
            } else {
                front = (front + 1) % capacity;
            }
            return true;
        }
    }

    void display() {
        int i;
        if (isEmpty()) {
            cout << endl
                 << "Пустая очередь" << endl;
        } else {
            cout << endl
                 << "Индекс FRONT -> " << front;
            cout << endl
                 << "Элементы -> ";
            for (i = front; i != back; i = (i + 1) % capacity) {
                cout << items[i] << "  ";
            }
            cout << items[i] << endl;
            cout << "Индекс BACK-> " << back << endl;
        }
    }

    void free() {
        delete items;
    }
};

#endif //RK3_QUEUE_H
