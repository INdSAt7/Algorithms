#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

void firstMode();
void secondMode();
int** multiplyMatrixWithUsAlg(int **A, int M, int N, int **B, int P, int Q);
int** multiplyMatrixWithVinogradsAlg(int **A, int M, int N, int **B, int P, int Q);
void compareMatrices(int **A, int M, int N, int **B, int P, int Q);
int** createArr(int rows, int cols);
void fillMatrix(int **Arr, int rows, int cols);
void printMatrix(int **Arr, int rows, int cols);
void randFillArr(int **Arr, int rows, int cols);

int main(){
    setlocale(0, "");

    int mode;
    printf("Enter the program mode:\n"
           "1 - Entering two matrices and comparing the results of their multiplication\n"
           "2 - CPU time measurement mode for calculating the product of matrices using different algorithms\n");

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

void firstMode() {
    int M, N, P, Q;

    cout << "Enter the number of rows and columns in the first matrix\n";
    cin >> M >> N;
    int **A = createArr(M, N);
    fillMatrix(A, M, N);

    cout << "Enter the number of rows and columns in the second matrix\n";
    cin >> P >> Q;
    int **B = createArr(P, Q);

    fillMatrix(B, P, Q);

    int** result_us_matrix = multiplyMatrixWithUsAlg(A, M, N, B, P, Q);
    int** result_vng_matrix = multiplyMatrixWithVinogradsAlg(A, M, N, B, P, Q);

    compareMatrices(result_us_matrix, M, Q, result_vng_matrix, M, Q);

    cout << "The result of matrix multiplication using the usual algorithm:\n";
    printMatrix(result_us_matrix, M, Q);

    cout << "The result of matrix multiplication using the Vinograd's algorithm:\n";
    printMatrix(result_vng_matrix, M, Q);

    delete[] A;
    delete[] B;
    delete[] result_vng_matrix;
    delete[] result_us_matrix;
}

void secondMode() {
    LARGE_INTEGER st1, st2, et1, et2, dt1, dt2;
    LARGE_INTEGER freq;
    QueryPerformanceCounter(&freq);

    for (int i = 1; i<6; i++){
        cout << "Multiplying matrices " << 20*i << "x" << 20*i << "\n";
        int **A = createArr(20*i, 20*i);
        randFillArr(A, 20*i, 20*i);
        int **B = createArr(20*i, 20*i);
        randFillArr(B, 20*i, 20*i);

        for (int counter = 0; counter < 10; counter++) {
            QueryPerformanceCounter(&st1);
                multiplyMatrixWithUsAlg(A,20*i, 20*i, B, 20*i, 20*i);
            QueryPerformanceCounter(&et1);

            QueryPerformanceCounter(&st2);
                multiplyMatrixWithVinogradsAlg(A,20*i, 20*i, B, 20*i, 20*i);
            QueryPerformanceCounter(&et2);

            //Calculating of execution time of algorithms
            dt1.QuadPart = ((et1.QuadPart - st1.QuadPart) * 1000000000) / freq.QuadPart;
            dt2.QuadPart = ((et2.QuadPart - st2.QuadPart) * 1000000000) / freq.QuadPart;

            cout << "Execution time of usual algorithm:" << dt1.QuadPart << " ns\n";
            cout << "Execution time of Vinograd's algorithm:" << dt2.QuadPart << " ns\n";
        }

        // Freeing dynamic memory storage matrix A
        for (int j = 0; j < 20*i; ++j){
            delete[] A[j];
        }
        delete[] A;

        // Freeing dynamic memory storage matrix B
        for (int j = 0; j < 20*i; ++j){
            delete[] B[j];
        }
        delete[] B;
        cout << "\n";
    }
}

int** multiplyMatrixWithUsAlg(int **A, int M, int N, int **B, int P, int Q){
    if (N != P){
        printf("Matrices can't be multiplied\n");
        exit(1);
    }

    int **C = createArr(M, Q);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int** multiplyMatrixWithVinogradsAlg(int **A, int M, int N, int **B, int P, int Q){
    if (N != P){
        printf("Matrices can't be multiplied\n");
        exit(1);
    }

    int **C = createArr(M, Q);

    int *MulH = new int[M];
    for (int i = 0; i < M; i++)//Filling matrix MulH
    {
        MulH[i] = 0;
        for (int k = 1; k <= N-1; k += 2) {
            MulH[i] += A[i][k - 1] * A[i][k];
        }
    }

    int *MulV = new int[Q];
    for (int j = 0; j < Q; j++)//Filling matrix MulV
    {
        MulV[j] = 0;
        for (int k = 1; k <= P-1; k += 2) {
            MulV[j] += B[k - 1][j] * B[k][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < Q; j++) {
            C[i][j] = -MulH[i] - MulV[j];
            for (int k = 1; k < N; k += 2) {
                C[i][j] += (A[i][k - 1] + B[k][j]) * (A[i][k] + B[k - 1][j]);
            }
        }
    }

    if (N % 2 == 1) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < Q; j++) {
                C[i][j] += A[i][N-1] * B[N-1][j];
            }
        }
    }

    delete []MulH;
    delete []MulV;

    return C;
}

void compareMatrices(int **A, int M, int N, int **B, int P, int Q) {
    if (M != P || N != Q) {
        printf("Matrices have different sizes: A[%dx%d]!=B[%dx%d]\n", M, N, P, Q);
        return;
    }

    int counter = 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[i][j]) {
                counter++;
                printf("A[%d][%d]!=B[%d][%d] (%d!=%d)\n",
                       i, j, i, j, A[i][j], B[i][j]);
            }
        }
    }

    if (counter == 0) {
        printf("Matrices are equal\n");
    } else {
        printf("Matrices have %d differences\n", counter);
    }
}

int** createArr(int rows, int cols){ //Creating matrix
    int **Matrix = new int* [rows];

    for (int i = 0; i < rows; i++)
    {
        Matrix[i] = new int [cols];
    }

    return Matrix;
}

void fillMatrix(int **Arr, int rows, int cols){
    printf("Enter %d elements of matrix:\n", rows * cols);

    for (int i = 0; i < rows; i++) {
        Arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            cin >> Arr[i][j];
        }
    }
}

void printMatrix(int **Arr, int rows, int cols){
    cout << "Result of multiplying matrices: " << rows << "x" << cols << "\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << Arr[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void randFillArr(int **Arr, int rows, int cols){ //Filling matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Arr[i][j] = rand() % 10;
        }
    }
}