//
// Created by agoru on 04.06.2024.
//

#include "matrix_sum_krm.h"

// Установка значений в массивы следующих элементов и первых элементов в зависимости от переданных аргументов
void setFirstIdxAndNextIdx(int idx, int *first_el_arr, vector<int> &next_el_arr, int an_size) {
    if (first_el_arr[idx] == -1) {
        first_el_arr[idx] = an_size;
        next_el_arr.push_back(an_size);
    } else {
        next_el_arr.push_back(first_el_arr[idx]);

        int cur_idx = first_el_arr[idx];

        while (next_el_arr[cur_idx] != first_el_arr[idx]) {
            cur_idx++;
        }

        next_el_arr[cur_idx] = an_size;
    }
}

// Поиск текущего индекса по столбцу или строке в зависимости от переданных аргументов
int getCurrentIdx(int index, int firstElementsArrLen, int *firstElementsArr, vector<int> nextElementsArr) {
    int idx = -1;
    while (idx == -1) {
        for (int i = 0; i < firstElementsArrLen; ++i) {
            if (firstElementsArr[i] == index) {
                idx = i;
                break;
            }
        }

        index = nextElementsArr[index];
    }

    return idx;
}

// Функция для сложения двух сжатых матриц по схеме Рейндбольдта - Местеньи
matrix sumPackMatrixByKRM(matrix &a, matrix &b) {
    vector<int> an;
    vector<int> nr;
    vector<int> nc;

    int *jr = new int[a.rows];
    int *jc = new int[a.cols];


    for (int i = 0; i < a.rows; ++i) {
        jr[i] = -1;
    }

    for (int i = 0; i < a.cols; ++i) {
        jc[i] = -1;
    }


    int cursor_a = 0;
    int cursor_b = 0;

    while (cursor_a < a.an.size() && cursor_b < b.an.size()) {
        // Ищем у элементов текущие индексы строки и столбца в матрице
        int col_a_idx = getCurrentIdx(a.nc[cursor_a], a.cols, a.jc, a.nc);
        int col_b_idx = getCurrentIdx(b.nc[cursor_b], b.cols, b.jc, b.nc);
        int row_a_idx = getCurrentIdx(a.nr[cursor_a], a.rows, a.jr, a.nr);
        int row_b_idx = getCurrentIdx(b.nr[cursor_b], b.rows, b.jr, b.nr);

        if ((row_a_idx < row_b_idx) || ((row_a_idx == row_b_idx) && (col_a_idx < col_b_idx))) {
            setFirstIdxAndNextIdx(row_a_idx, jr, nr, an.size());
            setFirstIdxAndNextIdx(col_a_idx, jc, nc, an.size());

            an.push_back(a.an[cursor_a]);
            cursor_a++;
        } else if (row_a_idx > row_b_idx || ((row_a_idx == row_b_idx) && (col_a_idx > col_b_idx))) {
            setFirstIdxAndNextIdx(row_b_idx, jr, nr, an.size());
            setFirstIdxAndNextIdx(col_b_idx, jc, nc, an.size());

            an.push_back(b.an[cursor_b]);
            cursor_b++;
        } else {
            if (a.an[cursor_a] + b.an[cursor_b]!=0){
                setFirstIdxAndNextIdx(row_a_idx, jr, nr, an.size());
                setFirstIdxAndNextIdx(col_a_idx, jc, nc, an.size());

                an.push_back(a.an[cursor_a] + b.an[cursor_b]);
            }

            cursor_a++;
            cursor_b++;
        }
    }

    while (cursor_a < a.an.size()) {
        int row_a_idx = getCurrentIdx(a.nr[cursor_a], a.rows, a.jr, a.nr);
        int col_a_idx = getCurrentIdx(a.nc[cursor_a], a.cols, a.jc, a.nc);

        setFirstIdxAndNextIdx(row_a_idx, jr, nr, an.size());
        setFirstIdxAndNextIdx(col_a_idx, jc, nc, an.size());

        an.push_back(a.an[cursor_a]);
        cursor_a++;
    }

    while (cursor_b < b.an.size()) {
        int row_b_idx = getCurrentIdx(b.nr[cursor_b], b.rows, b.jr, b.nr);
        int col_b_idx = getCurrentIdx(b.nc[cursor_b], b.cols, b.jc, b.nc);

        setFirstIdxAndNextIdx(row_b_idx, jr, nr, an.size());
        setFirstIdxAndNextIdx(col_b_idx, jc, nc, an.size());

        an.push_back(b.an[cursor_b]);
        cursor_b++;
    }

    return matrix{
            .rows=a.rows,
            .cols=a.cols,
            .an=an,
            .nr=nr,
            .nc=nc,
            .jr=jr,
            .jc=jc,
    };
}

// Функция для упаковки матрицы в сжатый формат по схеме Рейнбольдта-Местеньи
void packMatrixByKrm(matrix &m) {
    if (m.rows < 1 || m.cols < 1) {
        cout << "[Упаковка матрицы] матрица не должна быть нулевой" << endl;
        exit(1);
    }

    vector<int> an;
    vector<int> nr;
    vector<int> nc;

    int *jr = new int[m.rows];
    int *jc = new int[m.cols];

    for (int i = 0; i < m.rows; ++i) {
        jr[i] = -1;
    }

    for (int i = 0; i < m.cols; ++i) {
        jc[i] = -1;
    }


    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            if (m.matrix[i][j] != 0) {
                an.push_back(m.matrix[i][j]);

                if (jr[i] == -1) {
                    jr[i] = an.size() - 1;
                    nr.push_back(an.size() - 1);
                } else {
                    nr.push_back(jr[i]);

                    int cur_idx = jr[i];

                    while (nr[cur_idx] != jr[i]) {
                        cur_idx++;
                    }

                    nr[cur_idx] = an.size() - 1;
                }

                if (jc[j] == -1) {
                    jc[j] = an.size() - 1;
                    nc.push_back(an.size() - 1);
                } else {
                    nc.push_back(jc[j]);

                    int cur_idx = jc[j];

                    while (nc[cur_idx] != jc[j]) {
                        cur_idx++;
                    }

                    nc[cur_idx] = an.size() - 1;
                }
            }
        }
    }

    m.nc = nc;
    m.nr = nr;
    m.an = an;
    m.jr = jr;
    m.jc = jc;
}

// Функция для распаковки матрицы из сжатого формата Рейнбольдта-Местеньи
void unpackMatrixByKrm(matrix &m) {
    if (m.rows < 1 || m.cols < 1) {
        cout << "[Распаковка матрицы] матрица не должна быть нулевой" << endl;
        exit(1);
    }

    int **matrix = new int *[m.rows];

    for (int i = 0; i < m.rows; ++i) {
        matrix[i] = new int[m.cols];
        for (int j = 0; j < m.cols; ++j) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < m.an.size(); ++i) {
        int col_idx = -1;
        int row_idx = -1;
        int cur_nc = m.nc[i];
        int cur_nr = m.nr[i];

        while (col_idx == -1) {
            for (int j = 0; j < m.cols; ++j) {
                if (m.jc[j] == cur_nc) {
                    col_idx = j;
                    break;
                }
            }

            cur_nc = m.nc[cur_nc];
        }


        while (row_idx == -1) {
            for (int j = 0; j < m.rows; ++j) {
                if (m.jr[j] == cur_nr) {
                    row_idx = j;
                    break;
                }
            }

            cur_nr = m.nr[cur_nr];
        }

        matrix[row_idx][col_idx] = m.an[i];
    }

    m.matrix = matrix;
}


// Выводит массивы массивы запакованной матрицы Рейндбольдта - Местеньи
void printPackMatrixByKRM(matrix rm) {
    cout << endl;
    cout << "[Array AN]: ";

    for (int i = 0; i < rm.an.size(); ++i) {
        cout << rm.an[i] << " ";
    }

    cout << endl;
    cout << "[Array NR]: ";

    for (int i = 0; i < rm.nr.size(); ++i) {
        cout << rm.nr[i] << " ";
    }

    cout << endl;
    cout << "[Array NC]: ";

    for (int i = 0; i < rm.nc.size(); ++i) {
        cout << rm.nc[i] << " ";
    }

    cout << endl;
    cout << "[Array JR]: ";

    for (int i = 0; i < rm.rows; ++i) {
        cout << rm.jr[i] << " ";
    }

    cout << endl;
    cout << "[Array JC]: ";

    for (int i = 0; i < rm.cols; ++i) {
        cout << rm.jc[i] << " ";
    }
}
