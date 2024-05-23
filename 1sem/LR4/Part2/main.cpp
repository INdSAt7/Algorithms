#include <iostream>
#include <string>
#include <fstream>
#include "matrix.h"
#include "matrix_sum_krm.h"

using namespace std;

matrix readMatrixFromFile(const string&);
void printMatrix(matrix);
matrix sumMatrix(matrix &, matrix &);
matrix mulMatrix(matrix &a, matrix &b);
void compareMatrices(matrix &, matrix &);

int main() {
    // Сложение сжатых матриц
    cout<<"ADDITION OF COMPRESSED MATRICES\n";
    matrix matrix_rm_1 = readMatrixFromFile("source\\matrixRM1.txt");

    packMatrixByKrm(matrix_rm_1);

    cout << endl<< endl << "First matrix in compressed condition\n";
    printPackMatrixByKRM(matrix_rm_1);

    matrix matrix_rm_2 = readMatrixFromFile("sourc\\matrix_rm_2.txt");

    packMatrixByKrm(matrix_rm_2);

    cout<< endl << endl << "Second  matrix in compressed condition\n";
    printPackMatrixByKRM(matrix_rm_2);

    matrix sum_matrix_krm = sumPackMatrixByKRM(matrix_rm_1, matrix_rm_2);
    cout << endl<< endl << "Result of addition";
    printPackMatrixByKRM(sum_matrix_krm);
    unpackMatrixByKrm(sum_matrix_krm);

    cout << endl<< endl << "Regular matrix after addition\n";
    matrix sum_matrix=sumMatrix(matrix_rm_1, matrix_rm_2);
    printMatrix(sum_matrix);

    compareMatrices(sum_matrix_krm, sum_matrix);

    // Умножение сжатых матриц
    cout<<"MULTIPLYING OF COMPRESSED MATRICES\n";
    matrix matrix_rm_3 = readMatrixFromFile("source\\multiplying1.txt");

    packMatrixByKrm(matrix_rm_3);

    cout << endl << "Third matrix in compressed condition\n";
    printPackMatrixByKRM(matrix_rm_3);

    matrix matrix_rm_4 = readMatrixFromFile("source\\multiplying2.txt");

    packMatrixByKrm(matrix_rm_4);

    cout<< endl << endl << "Fourth matrix in compressed condition\n";
    printPackMatrixByKRM(matrix_rm_4);

    cout << endl<< endl << "Result of multiplying";
    matrix mul_matrix_krm=mulPackMatrixByKRM(matrix_rm_3, matrix_rm_4);
    printPackMatrixByKRM(mul_matrix_krm);
    unpackMatrixByKrm(mul_matrix_krm);

    cout << endl<< endl << "Regular matrix after multiplying\n";
    matrix mul_matrix=mulMatrix(matrix_rm_3, matrix_rm_4);
    printMatrix(mul_matrix);

    compareMatrices(mul_matrix_krm, mul_matrix);

    // Очистим динамическую память
    delete[] matrix_rm_1.matrix;
    matrix_rm_1.an.clear();
    matrix_rm_1.nr.clear();
    matrix_rm_1.nc.clear();
    delete matrix_rm_1.jr;
    delete matrix_rm_1.jc;

    delete[] matrix_rm_2.matrix;
    matrix_rm_2.an.clear();
    matrix_rm_2.nr.clear();
    matrix_rm_2.nc.clear();
    delete matrix_rm_2.jr;
    delete matrix_rm_2.jc;

    delete[] sum_matrix.matrix;

    delete[] sum_matrix_krm.matrix;
    sum_matrix_krm.an.clear();
    sum_matrix_krm.nr.clear();
    sum_matrix_krm.nc.clear();
    delete sum_matrix_krm.jr;
    delete sum_matrix_krm.jc;

    delete[] matrix_rm_3.matrix;
    matrix_rm_3.an.clear();
    matrix_rm_3.nr.clear();
    matrix_rm_3.nc.clear();
    delete matrix_rm_3.jr;
    delete matrix_rm_3.jc;

    delete[] matrix_rm_4.matrix;
    matrix_rm_4.an.clear();
    matrix_rm_4.nr.clear();
    matrix_rm_4.nc.clear();
    delete matrix_rm_4.jr;
    delete matrix_rm_4.jc;

    delete[] mul_matrix.matrix;

    delete[] mul_matrix_krm.matrix;
    mul_matrix_krm.an.clear();
    mul_matrix_krm.nr.clear();
    mul_matrix_krm.nc.clear();
    delete mul_matrix_krm.jr;
    delete mul_matrix_krm.jc;
}

matrix readMatrixFromFile(const string& filename) {
    ifstream fin(filename);

    if (!fin.is_open()) {
        cout << "Unable to open the file: " << filename << endl;
        exit(1);
    }

    matrix m;
    fin >> m.rows >> m.cols;

    m.matrix = new int*[m.rows];
    for (int i = 0; i < m.rows; ++i) {
        m.matrix[i] = new int[m.cols];
        for (int j = 0; j < m.cols; ++j) {
            fin >> m.matrix[i][j];
        }
    }

    fin.close();
    return m;
}

// Выводит последовательно все элементы матрицы
void printMatrix(matrix m) {
    printf("Result matrix %dx%d:\n", m.rows, m.cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            cout << m.matrix[i][j] << " ";
        }

        cout << endl;
    }

    cout << endl;
}

// Функция для сложения двух матриц
matrix sumMatrix(matrix &a, matrix &b) {
    matrix c;
    c.matrix = new int *[a.rows];
    c.rows = a.rows;
    c.cols = a.cols;

    for (int i = 0; i < a.rows; ++i) {
        c.matrix[i] = new int[a.cols];
        for (int j = 0; j < a.cols; ++j) {
            c.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }

    return c;
}

// Функция для умножения двух матриц
matrix mulMatrix(matrix &a, matrix &b) {
    if (a.cols != b.rows) {
        cout << "Number of columns of the first matrix not equal to number of rows of the second matrix. Multiplying is impossible"
             << endl;
        exit(0);
    }

    matrix c;
    c.matrix = new int *[a.rows];
    c.rows = a.rows;
    c.cols = b.cols;

    for (int i = 0; i < a.rows; ++i) {
        c.matrix[i] = new int[b.cols];
        for (int j = 0; j < b.cols; ++j) {
            for (int k = 0; k < a.cols; k++) {
                c.matrix[i][j] += a.matrix[i][k] * b.matrix[k][j];
            }
        }
    }

    return c;
}

// Функция для сравнения двух матриц в стандартном виде
void compareMatrices(matrix &matrix_A, matrix &matrix_B) {
    if (matrix_A.rows != matrix_B.rows || matrix_A.cols != matrix_B.cols) {
        printf("Матрицы имеют разный размер: A[%dx%d]!=B[%dx%d]\n",
               matrix_A.rows, matrix_A.cols, matrix_B.rows, matrix_B.cols);

        return;
    }

    int counter = 0;

    for (int i = 0; i < matrix_A.rows; i++) {
        for (int j = 0; j < matrix_A.cols; j++) {
            if (matrix_A.matrix[i][j] != matrix_B.matrix[i][j]) {
                counter++;
                printf("A[%d][%d]!=B[%d][%d] (%d!=%d)\n",
                       i, j, i, j, matrix_A.matrix[i][j], matrix_B.matrix[i][j]);
            }
        }
    }

    if (counter == 0) {
        printf("Результирующие матрицы совпадают\n\n");
    } else {
        printf("Результирующие матрицы имеют %d отличий\n\n", counter);
    }
}