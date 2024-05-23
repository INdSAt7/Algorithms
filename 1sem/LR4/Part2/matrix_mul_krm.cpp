//
// Created by agoru on 23.05.2024.
//

#include "matrix.h"
#include "matrix_sum_krm.h"

// Функция для умножения двух сжатых матриц по схеме Рейндбольдта - Местеньи
matrix mulPackMatrixByKRM(matrix &a, matrix &b) {
    if (a.cols != b.rows) {
        cout << "Количество столбцов первой матрицы не равно количеству строк второй матрицы, умножение невозможно"
             << endl;
        exit(0);
    }

    int indexRow; // индекс строки
    int indexCol; // индекс столбца

    vector<int> an;
    vector<int> nr;
    vector<int> nc;

    int *jr = new int[a.rows];
    int *jc = new int[b.cols];

    for (int i = 0; i < a.rows; ++i) {
        jr[i] = -1;
    }

    for (int i = 0; i < b.cols; ++i) {
        jc[i] = -1;
    }

    for (int i = 0; i < a.rows; ++i) { // внешний цикл по строкам первой матрицы
        indexRow = a.jr[i];
        // Если строка пуста, то переходим к следующей строке
        if (indexRow == -1) {
            continue;
        }

        for (int j = 0; j < b.cols; ++j) { // цикл по столбцам второй матрицы
            indexCol = b.jc[j];
            // Если столбец пуст, то переходим к следующему столбцу
            if (indexCol == -1) {
                continue;
            }

            int sum = 0;

            bool rowEnd = false;
            while (!rowEnd) { // цикл прохода по текущей строке
                bool colEnd = false;
                int curRowElemIdx = getCurrentIdx(indexRow, a.cols, a.jc, a.nc);

                while (!colEnd) { // цикл прохода по текущему столбцу
                    int curColElemIdx = getCurrentIdx(indexCol, b.rows, b.jr, b.nr);
                    if (curColElemIdx >
                        curRowElemIdx) { // если индекс элемента в колонке больше индекса элемента в строке, то нет смысла продолжать цикл
                        break;
                    }

                    //проверка совпадения индекса элемента строки и стобца
                    if (curColElemIdx == curRowElemIdx) {
                        sum += a.an[indexRow] * b.an[indexCol];
                    }

                    indexCol = b.nc[indexCol]; // следующий индекс столбца

                    if (indexCol == b.jc[j]) { //если прошли круг - выход
                        colEnd = true;
                    }
                }

                indexRow = a.nr[indexRow]; // следующий индекс строки

                if (indexRow == a.jr[i]) { //если прошли круг - выход
                    rowEnd = true;
                }
            }

            if (sum != 0) {
                setFirstIdxAndNextIdx(i, jr, nr, an.size()); // заполнение массивов jr и nr
                setFirstIdxAndNextIdx(j, jc, nc, an.size()); // заполнение массивов jc и nc
                an.push_back(sum); // заполнение AN
            }
        }
    }

    return matrix{
            .rows=a.rows,
            .cols=b.cols,
            .an=an,
            .nr=nr,
            .nc=nc,
            .jr=jr,
            .jc=jc,
    };
}
