#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int length;
    cout << "Enter length of array\n";
    cin >> length;

    int *arr = new int[length]; // Динамическое выделение памяти для массива

    cout << "Enter " << length << " elements:\n";
    for (int i = 0; i < length; i++) {
        cin >> arr[i];
    }

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
