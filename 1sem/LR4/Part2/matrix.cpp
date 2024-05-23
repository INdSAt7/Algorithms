//
// Created by agoru on 23.05.2024.
//

#include "matrix.h"

// Функция для упаковки матрицы в сжатый формат по схеме Дженнинга
void packMatrix(matrix &m) {
    vector<int> an;
    an.push_back(m.matrix[0][0]);

    int *d = new int[m.rows];

    d[0] = 0;

    for (int i = 1; i < m.rows; ++i) {
        bool wasNotZeroElement = false;

        for (int j = 0; j <= i; ++j) {
            if (m.matrix[i][j] != 0 || wasNotZeroElement || i == j) {
                wasNotZeroElement = true;
                an.push_back(m.matrix[i][j]);
            }
        }

        d[i] = an.size() - 1;
    }

    m.an = an;
    m.d = d;
}

// Функция для распаковки матрицы
void unpackMatrix(matrix &m) {
    m.matrix = new int *[m.rows];
    m.matrix[0] = new int[m.cols];
    m.matrix[0][0] = m.an[0];

    for (int i = 1; i < m.rows; i++) {
        m.matrix[i] = new int[m.cols];
        int not_zero_el_count = m.d[i] - m.d[i - 1] - 1;

        for (int j = 0; j <= i; j++) {
            if (not_zero_el_count > 0 && j == i - not_zero_el_count) {
                m.matrix[i][j] = m.an[m.d[i] - not_zero_el_count];
                m.matrix[j][i] = m.an[m.d[i] - not_zero_el_count];
                not_zero_el_count--;
                continue;
            }

            if (i == j) {
                m.matrix[i][j] = m.an[m.d[i]];
                m.matrix[j][i] = m.an[m.d[i]];
                continue;
            }

            m.matrix[i][j] = 0;
            m.matrix[j][i] = 0;
        }
    }
}


// Функция для сложения двух сжатых матриц
matrix sumPackMatrix(matrix &a, matrix &b) {
    matrix c;

    vector<int> an;
    an.push_back(a.an[0] + b.an[0]);

    int *d = new int[a.rows];

    d[0] = 0;

    for (int i = 1; i < a.rows; ++i) {
        int diff_a_d = a.d[i] - a.d[i - 1];
        int diff_b_d = b.d[i] - b.d[i - 1];

        int diff = abs(diff_a_d - diff_b_d);

        bool flag =false;
        if (diff != 0) {
            if (diff_a_d > diff_b_d) {
                for (int j = 1; j <= (diff); ++j) {
                    int cur_el = a.an[a.d[i - 1] + j];
                    if (cur_el!=0 && !flag){
                        flag= true;
                    }
                    an.push_back(cur_el);
                }

                diff_a_d -= diff;
            } else {
                for (int j = 1; j <= (diff); ++j) {
                    int cur_el =b.an[b.d[i - 1] + j];
                    if (cur_el!=0 && !flag){
                        flag= true;
                    }
                    an.push_back(cur_el);
                }
            }

            bool wasNotZeroElement = flag;
            for (int j = 1; j <= diff_a_d; ++j) {
                int sum = a.an[a.d[i] - diff_a_d + j] + b.an[b.d[i] - diff_a_d + j];

                if (sum == 0 && !wasNotZeroElement  && a.d[i] != a.d[i - 1] + j) {
                    continue;
                }

                an.push_back(sum);
                wasNotZeroElement = true;
            }

            d[i] = an.size() - 1;
        } else {
            bool wasNotZeroElement = false;
            for (int j = 1; j <= (a.d[i] - a.d[i - 1]); ++j) {
                int sum = a.an[a.d[i - 1] + j] + b.an[b.d[i - 1] + j];

                if (sum == 0 && !wasNotZeroElement && a.d[i] != a.d[i - 1] + j) {
                    continue;
                }

                an.push_back(sum);
                wasNotZeroElement = true;
            }

            d[i] = an.size() - 1;
        }
    }

    c.rows = a.rows;
    c.cols = a.cols;
    c.an = an;
    c.d = d;

    return c;
}

// Выводит массивы AN и D
void printPackMatrix(matrix m) {
    cout << "Результирующая запакованная матрица " << m.rows << "x" << m.cols << endl;
    cout << "Массив AN: ";
    for (int i = 0; i < m.an.size(); i++) {
        cout << m.an[i] << " ";
    }

    cout << endl;

    cout << "Массив D: ";
    for (int i = 0; i < m.rows; i++) {
        cout << m.d[i] << " ";
    }

    cout << endl;
}

// Функция для сложения двух сжатых матриц через сами матрицы
matrix sumPackMatrixExcessive(matrix &a, matrix &b) {
    matrix c;

    vector<int> an;
    an.push_back(a.an[0] + b.an[0]);

    int *d = new int[a.rows];

    d[0] = 0;

    for (int i = 1; i < a.rows; ++i) {
        bool wasNotZeroElement = false;

        for (int j = 0; j <= i; ++j) {
            if ((a.matrix[i][j] + b.matrix[i][j] != 0) || (i == j) || wasNotZeroElement) {
                wasNotZeroElement = true;
                an.push_back(a.matrix[i][j] + b.matrix[i][j]);
            }
        }

        d[i] = an.size() - 1;
    }

    c.rows = a.rows;
    c.cols = a.cols;
    c.an = an;
    c.d = d;

    return c;
}