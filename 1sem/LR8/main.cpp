#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

int* readMatrixFromFile(string filename, int &n);

int main() {
    int length;


    int *arr = new int[length]; // Динамическое выделение памяти для массива

//    cout << "Enter length of array\n";
//    cin >> length;

//    cout << "Enter " << length << " elements:\n";
//    for (int i = 0; i < length; i++) {
//        cin >> arr[i];
//    }

    arr = readMatrixFromFile("Array.txt", length);

    sort(arr, arr + length);

    int key;
    cout << "Enter the desired number:\n";
    cin >> key;

    int low = 0;
    int high = length - 1;
    bool isFound = false;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == key) {
            cout << "Serial number of the desired number is: " << mid << endl;
            isFound = true;
            break;
        } else if (arr[mid] > key) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (!isFound) {
        cout << "Desired number not found" << endl;
    }

    delete[] arr; // Освобождение памяти
    return 0;
}

int* readMatrixFromFile(string filename, int &n){
    ifstream fin;
    fin.open(filename);


    string str;

    if (!fin.is_open()) {
        cout << "Unable to open the file: " << filename << endl;
        exit(1);
    } else {
        fin >> str;
        n = stoi(str);

        int *arr = new int[n];

        for (int i = 0; i < n; i++) {
            fin >> str;
            arr[i] = stoi(str);
        }

        return arr;
    }
}