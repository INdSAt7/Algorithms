#include <iostream>
#include <Windows.h>
#include <random>
using namespace std;


int distanceLevinshteinIter(string firstWord, string secondWord);
int distanceLevinshteinRec(string w1, int len1, string w2, int len2, int **Matrix);
int distanceLevinshteinRecCache(string firstWord, int len1, string secondWord, int len2);
int distanceDamerauLevinshtein(string w1, int len1, string w2, int len2);
int chooseOper(string w1, int len1, string w2, int len2, int **Matrix);
int minimum(int a, int b);
int minimum(int a, int b, int c);
void printMatrix(int **Arr, int rows, int cols);
int** createArr(int rows, int cols);
char **createArrStr(int numberofWords, int len);
void firstMode();
void secondMode();
void randFillArr(int len, string *Arr);

int main(){
    int mode;
    printf("Enter the program mode:\n"
           "1 - Entering two words and comparing the results of Levinstein distance calculated with different algorithms\n"
           "2 - CPU time measurement mode for calculating the Levinstein distance using different algorithms\n");

    cin >> mode;

    switch (mode) {
        case 1:
            firstMode();
            break;
        case 2:
            secondMode();
            break;
        default:
            cout << "There is no such mode: " << mode << "\n";
    }
}

void firstMode(){
    string firstWord, secondWord;

    cout << "Enter first string to analyze\n";
    cin >> firstWord;

    cout << "Enter second string to analyze\n";
    cin >> secondWord;

    int a = distanceLevinshteinIter(firstWord, secondWord);
    cout << "Result Iter method: " << a << "\n";

    int b = distanceLevinshteinRec(firstWord, firstWord.length(), secondWord , secondWord.length(), NULL);
    cout << "Result Rec method: " << b << "\n";

    int c = distanceLevinshteinRecCache(firstWord, firstWord.length(), secondWord , secondWord.length());
    cout << "Result Rec method with cache: " << c << "\n";

    int d = distanceDamerauLevinshtein(firstWord, firstWord.length(), secondWord , secondWord.length());
    cout << "Result Damerau - Levenshtein method: " << c << "\n";
}

void secondMode(){
    LARGE_INTEGER st1, et1;
    LARGE_INTEGER freq;
    QueryPerformanceCounter(&freq);

    char **Arr = new char *[14];

    int currentLength = 2;

    for (int i = 0; i < 7; i++) {
        Arr[2 * i] = new char[currentLength];
        Arr[2 * i + 1] = new char[currentLength];

        for (int j = 0; j < currentLength; j++) {
            Arr[2 * i][j] = rand() % 93 + 33;
            Arr[2 * i + 1][j] = rand() % 93 + 33;
        }

        currentLength += 2;
    }


    cout << "Execution time of iterative algorithm:\n";
    for (int i = 0; i < 7; i++) {
        QueryPerformanceCounter(&st1);
        distanceLevinshteinIter(Arr[2*i], Arr[2*i+1]);
        QueryPerformanceCounter(&et1);

         cout << "Strings length = "<< 2*(i+1) << ", Time: "<<
             ((et1.QuadPart - st1.QuadPart) * 1000000000000) / freq.QuadPart << " ns\n";
    }

    cout << "\n\n";

    cout << "Execution time of recursion algorithm:\n";
    for (int i = 0; i < 5; i++) {
        QueryPerformanceCounter(&st1);
        distanceLevinshteinRec(Arr[2*i], 2*(i+1), Arr[2*i+1], 2*(i+1), NULL);
        QueryPerformanceCounter(&et1);
        cout << "Strings length = "<< 2*(i+1) << ", Time: "<<
             ((et1.QuadPart - st1.QuadPart) * 1000000000000) / freq.QuadPart << " ns\n";
    }

    cout << "\n\n";

    cout << "Execution time of recursion algorithm with cache:\n";
    for (int i = 0; i < 7; i++) {
        QueryPerformanceCounter(&st1);
        distanceLevinshteinRecCache(Arr[2*i], 2*(i+1), Arr[2*i+1], 2*(i+1));
        QueryPerformanceCounter(&et1);
        cout << "Strings length = "<< 2*(i+1) << ", Time: "<<
             ((et1.QuadPart - st1.QuadPart) * 1000000000000) / freq.QuadPart << " ns\n";
    }

    cout << "\n\n";

    cout << "Execution time of algorithm Damerau - Levinshtein:\n";
    for (int i = 0; i < 7; i++) {
        QueryPerformanceCounter(&st1);
        distanceDamerauLevinshtein(Arr[2*i], 2*(i+1), Arr[2*i+1], 2*(i+1));
        QueryPerformanceCounter(&et1);
        cout << "Strings length = "<< 2*(i+1) << ", Time: "<<
             ((et1.QuadPart - st1.QuadPart) * 1000000000000) / freq.QuadPart << " ns\n";
    }


    // Освобождение памяти
    for (int i = 0; i < 14; i++) {
        delete[] Arr[i];
    }

    delete[] Arr;
}

int distanceLevinshteinRecCache(string w1, int len1, string w2, int len2){
    int **Matrix = createArr(len1 + 1, len2 + 1);

    if (len1 == 0) {
        return len2;
    }

    if (len2 == 0) {
        return len1;
    }

    return chooseOper(w1, len1, w2, len2, Matrix);
}

int distanceLevinshteinRec(string w1, int len1, string w2, int len2, int **Matrix) {
    if (Matrix == NULL || Matrix[len1][len2] == -1) {
        if (len1 == 0) {
            return len2;
        }

        if (len2 == 0) {
            return len1;
        }

        if (Matrix != NULL) {
            Matrix[len1][len2] = chooseOper(w1, len1, w2, len2, Matrix);
            return Matrix[len1][len2];
        } else {
            return chooseOper(w1, len1, w2, len2, Matrix);
        }
    } else
        return Matrix[len1][len2];
}

int distanceLevinshteinIter(string w1, string w2)
{
    int deleteCost = 1;
    int insertCost = 1;
    int replaceCost;

    int n = w1.length();
    int m = w2.length();

    if (n == 0 || m == 0){
        if (n == 0)
            return m;

        if (m == 0)
            return n;
        }

    int **Matrix = createArr(n+1, m+1);

    for (int i = 0; i < n+1; i++)
        Matrix[i][0] = i;

    for (int j = 0; j < m+1; j++)
        Matrix[0][j] = j;

    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < m+1; j++){

            if (w1[i - 1] == w2[j - 1])
                replaceCost = 0;
            else
                replaceCost = 1;

            Matrix[i][j] = minimum(Matrix[i - 1][j] + deleteCost, //deletion
                                   Matrix[i][j - 1] + insertCost, // insertion
                                   Matrix[i - 1][j - 1] + replaceCost); // replacement
        }
    }

    int res = Matrix[n][m];

    for (int i = 0; i < n; i++)
        delete[] Matrix[i];

    delete[] Matrix;

    return res;
}

int distanceDamerauLevinshtein(string w1, int len1, string w2, int len2){
    int deleteCost = 1;
    int insertCost = 1;
    int replaceCost;

    int n = w1.length();
    int m = w2.length();

    if (n == 0 || m == 0){
        if (n == 0)
            return m;

        if (m == 0)
            return n;
    }

    int **Matrix = createArr(n+1, m+1);

    for (int i = 0; i < n+1; i++)
        Matrix[i][0] = i;

    for (int j = 0; j < m+1; j++)
        Matrix[0][j] = j;

    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < m+1; j++){

            if (w1[i - 1] == w2[j - 1])
                replaceCost = 0;
            else
                replaceCost = 1;

            Matrix[i][j] = minimum(Matrix[i - 1][j] + deleteCost, //deletion
                                   Matrix[i][j - 1] + insertCost, // insertion
                                   Matrix[i - 1][j - 1] + replaceCost); // replacement

            if (i > 1 && j > 1 && w1[i - 1] == w2[j - 2] && w1[i - 2] == w2[j - 1])
            {
                Matrix[i][j] = minimum(Matrix[i][j],Matrix[i - 2][j - 2] + 1); // перестановка
            }
        }
    }

    int res = Matrix[n][m];

    for (int i = 0; i < n; i++)
        delete[] Matrix[i];

    delete[] Matrix;

    return res;
}

int chooseOper(string w1, int len1, string w2, int len2, int **Matrix){
    int replaceCost;

    if (w1[len1 - 1] == w2[len2 - 1])
        replaceCost = 0;
    else
        replaceCost = 1;

    int deletion = distanceLevinshteinRec(w1.substr(0, len1 - 1), len1 - 1, w2, len2,
                                          Matrix) + 1;
    int insert = distanceLevinshteinRec(w1, len1, w2.substr(0, len2 - 1), len2 - 1,
                                        Matrix) + 1;
    int replace = distanceLevinshteinRec(w1.substr(0, len1 - 1), len1 - 1,
                                         w2.substr(0, len2 - 1), len2 - 1,
                                         Matrix) + replaceCost;

    return minimum(deletion, insert, replace);
}

int minimum(int a, int b){
    if(a > b)
        a = b;
    return a;
}

int minimum(int a, int b, int c){
    if(a > b)
        a = b;

    if(a > c)
        a = c;

    return a;
}

void printMatrix(int **Arr, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << Arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int **createArr(int rows, int cols){ //Creating matrix
    int **Matrix = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        Matrix[i] = new int [cols];
        for (int j = 0; j < cols; j++) {
            Matrix[i][j] = -1;
        }
    }

    return Matrix;
}

char **createArrStr(int numberofWords, int len){ //Creating matrix
    char **Arr = new char* [numberofWords];

    for (int i = 0; i < numberofWords; i++)
    {
        Arr[i] = new char [len];
    }

    return Arr;
}