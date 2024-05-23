//
// Created by agoru on 23.05.2024.
//

#ifndef PART2_MATRIX_SUM_KRM_H
#define PART2_MATRIX_SUM_KRM_H


#include "matrix.h"

matrix sumPackMatrixByKRM(matrix &, matrix &);
matrix mulPackMatrixByKRM(matrix &, matrix &);
void packMatrixByKrm(matrix &);
void printPackMatrixByKRM(matrix);
void unpackMatrixByKrm(matrix &m);
int getCurrentIdx(int index, int firstElementsArrLen, int *firstElementsArr, vector<int> nextElementsArr);
void setFirstIdxAndNextIdx(int idx, int *first_el_arr, vector<int> &next_el_arr, int an_size);


#endif //PART2_MATRIX_SUM_KRM_H
