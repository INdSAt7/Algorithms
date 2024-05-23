//
// Created by agoru on 23.05.2024.
//

#ifndef PART2_MATRIX_H
#define PART2_MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

typedef struct {
    int **matrix;
    int rows;
    int cols;
    vector<int> an;
    int *d;
    vector<int> nr;
    vector<int> nc;
    int *jr;
    int *jc;
} matrix;

void packMatrix(matrix &);
void unpackMatrix(matrix &);
matrix sumPackMatrix(matrix &, matrix &);
void printPackMatrix(matrix);
matrix sumPackMatrixExcessive(matrix &, matrix &);


#endif //PART2_MATRIX_H
