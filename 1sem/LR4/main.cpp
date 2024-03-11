#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int** createMatrix(int n, int m);
int** readMatrixFromFile(string filename, int &n, int &m);
void printMatrix(int **Arr, int rows, int cols);
int* matrixCompression1(int **Matrix, int *D, int &rows, int &cols);
int* matrixAddition1(int *AN1, int *AN2, int *D1, int *D2, int &n, int &counter, int *DC);
int** matrixUnpacking1(int *Matrix, int *D, int &n);
int firstPart();

int main(){
    int mode;
    cout << "Enter the program mode:\n" <<
         "1 - Reading 2 matrices from files, their compression and addition\n";
//         "2 - Entering two boundaries, start number of integration sections and factor. Calculation of integral with a given"
//         " accuracy\n";
    cin >> mode;

    switch (mode) {
        case 1:
            firstPart();
            break;
//        case 2:
//            secondPart();
//            break;
        default:
            cout << "There is no such mode: " << mode << "\n";
    }

    return 0;
}

int** readMatrixFromFile(string filename, int &n, int &m){
    ifstream fin;
    fin.open(filename);

    int** Matrix;

    string str;

    if (!fin.is_open()) {
        cout << "Unable to open the file: " << filename << endl;
        exit(1);
    } else {
        fin >> str;
        n = stoi(str);

        fin >> str;
        m = stoi(str);

        Matrix = createMatrix(n, m);

        for (int i = 0 ; i<n; i++)
            for (int j = 0; j < m; j++) {
                fin >> str;
                Matrix[i][j] = stoi(str);
            }
    }
    return Matrix;
}

int** createMatrix(int n, int m){
    int** Matrix = new int *[n];
    for (int i = 0; i<n; i++)
        Matrix[i] = new int[m];

    return Matrix;
}

void printMatrix(int **Arr, int rows, int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << Arr[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

int* matrixCompression1(int **Matrix, int *D, int &rows, int &cols) {
    int counter = 0;
    bool flag = false;
    int* AN;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j || Matrix[i][j] != 0)
                flag = true;
            if (flag)
                counter++;
        }
        flag = false;
        D[i] = counter - 1;
        cout << D[i] << " ";
    }

    AN = new int[D[rows-1]+1];

    cout << "\n";

    counter = 0;

    for (int i = 0; i<rows; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j || Matrix[i][j] != 0)
                flag = true;
            if (flag) {
                AN[counter] = Matrix[i][j];
                cout << AN[counter] << " ";
                counter++;
            }
        }
        flag = false;
    }
    cout << "\n\n";

    return AN;
}

int* matrixAddition1(int *AN1, int *AN2, int *D1, int *D2, int &n, int &counter, int *DC){
    counter = 0;
    int d;
    bool flag = false;
    int i, j;
    DC[0] = 0;

    for (i = 1; i<n; i++){
        if (D1[i] - D1[i-1] != D2[i] - D2[i-1]){
            if (D1[i] - D1[i-1] > D2[i] - D2[i-1])
                counter += D1[i] - D1[i-1];

            else
                counter += D2[i] - D2[i-1];

        } else {
            d = D1[i] - D2[i];

            for (j = D1[i-1] + 1; j <= D1[i]; j++) {
                if (flag || AN1[j] + AN2[j-d] != 0) {
                    flag = true;
                    counter++;
                }

                if (!flag && j == D1[i])
                    counter++;
            }
            flag = false;
        }
        DC[i] = counter;
    }

    int* C = new int[counter];
    counter = 1;
    C[0] = AN1[0] + AN2[0];

    for (i = 1; i<n; i++){

        int lenD1 = D1[i] - D1[i-1];
        int lenD2 = D2[i] - D2[i-1];

        if(lenD1 > lenD2) {
            for (j = D2[i-1] + 1; j <= D1[i]; j++) {
                C[counter] = AN1[j];
                counter++;
            }

            for (j = 0; j < D2[i] - D2[i-1]; j++)
                C[counter - j - 1] += AN2[D2[i] - j];

        }

        else if (lenD1 < lenD2) {

            for (j = D2[i-1] + 1; j <= D2[i]; j++) {
                C[counter] = AN2[j];
                counter++;
            }


            for (j = 0; j < D1[i] - D1[i-1]; j++)
                C[counter - 1 - j] += AN1[D1[i] - j];

        }

        else {
            d = D1[i] - D2[i];

            for (j = D1[i - 1] + 1; j <= D1[i]; j++) {
                if (flag || AN1[j] + AN2[j - d] != 0) {
                    flag = true;
                    C[counter++] = AN1[j] + AN2[j - d];
                }

                if (!flag && j == D1[i])
                    C[counter++] = 0;
            }
            flag = false;
        }
    }
    return C;
}

int** matrixUnpacking1(int *Matrix, int *D, int &n){
    int **Result = new int *[n];
    for (int i = 0; i<n; i++)
        Result[i] = new int[n];

    for (int i = 0; i<n; i++)
        for (int j = 0; j<n; j++)
            Result[i][j] = 0;

    Result[0][0] = Matrix[0];
    for (int i = 1; i<n; i++)
        for (int j = 0; j < D[i] - D[i-1]; j++) {
            Result[i][i-j] = Matrix[D[i] - j];
            Result[i-j][i] = Result[i][i-j];
        }
    return Result;
}

int firstPart(){
    int n1, m1, n2, m2, CSize;

    int **Matrix1 = readMatrixFromFile("matrix1.txt", n1, m1);
    int **Matrix2 = readMatrixFromFile("matrix2.txt", n2, m2);

    int *AN1;
    int *AN2;

    cout << "Matrix 1:\n";
    printMatrix(Matrix1, n1, m1);

    cout << "Matrix 2:\n";
    printMatrix(Matrix2, n2, m2);

    int* D1 = new int[n1];
    int* D2 = new int[n2];
    int* DC = new int[n1];
    int** Result;

    cout << "Matrix1 in compressed view:\n";
    AN1 = matrixCompression1(Matrix1, D1, n1, m1);

    cout << "Matrix2 in compressed view:\n";
    AN2 = matrixCompression1(Matrix2, D2, n2, m2);

    int* C = matrixAddition1(AN1, AN2, D1, D2, n1, CSize, DC);

    cout << "Result of addition matrices in compressed view:\n";

    for(int i = 0; i<CSize; i++)
        cout << C[i] << " ";

    cout << "\n";

    for(int i = 0; i<n1; i++)
        cout << DC[i] << " ";

    Result = matrixUnpacking1(C, DC, n1);

    cout << "\n\nResult of addition matrices\n";
    for (int i = 0; i<n1; i++) {
        for (int j = 0; j < n1; j++)
            cout << Result[i][j] << "\t";
        cout << "\n";
    }

    delete[] AN1;
    delete[] D1;
    delete[] AN2;
    delete[] D2;
    delete[] C;
    delete[] DC;

    for (int i = 0; i<n1; i++) {
        delete[] Matrix1[i];
        delete[] Matrix2[i];
        delete[] Result[i];
    }
    delete[] Matrix1;
    delete[] Matrix2;
    delete[] Result;
}

int matrixCompression2(int **Matrix, int *AN, int *NR, int *NC, int *JR, int *JC){

}

int secondPart(){
    int n1, m1, n2, m2, CSize;

    int **Matrix1 = readMatrixFromFile("matrix1.txt", n1, m1);
    int **Matrix2 = readMatrixFromFile("matrix2.txt", n2, m2);

    int *AN1;
    int *AN2;

    cout << "Matrix 1:\n";
    printMatrix(Matrix1, n1, m1);

    cout << "Matrix 2:\n";
    printMatrix(Matrix2, n2, m2);
}