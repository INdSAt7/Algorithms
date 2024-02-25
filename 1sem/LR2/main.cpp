#include <iostream>
#include <cmath>
using namespace std;

void firstMode();
void secondMode();
float dxCalculator(float x1, float x2, int n);
float yCurCalculator(float xCur);
float leftRectangle(float x1, float x2, int n);
float rightRectangle(float x1, float x2, int n);
float Trapezoid(float x1, float x2, int n);
void accIntegration(float integrMethod(float, float, int), float x1, float x2, int n, int Nmax, float Mul);

int main() {
    int mode;
    cout << "Enter the program mode:\n" <<
    "1 - Entering two boundaries and number of integration sections. Calculating of integral with input data\n" <<
    "2 - Entering two boundaries, start number of integration sections and factor. Calculation of integral with a given"
    " accuracy\n";
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

    return 0;
}

void firstMode(){
    int N;
    float X1, X2;

    cout << "In this program will be integrate function y(x) = 0,5*sin(x)+x\n";

    cout << "Enter left and right boundaries of integration\n";
    cin >> X1 >> X2;
    cout << "Enter number of integration sections\n";
    cin >> N;

    cout << "Result of integration by the RIGHT RECTANGLE METHOD: " << rightRectangle(X1, X2, N) << "\n";
    cout << "Result of integration by the LEFT RECTANGLE METHOD: " << leftRectangle(X1, X2, N) << "\n";
    cout << "Result of integration by the TRAPEZOID METHOD: " << Trapezoid(X1, X2, N) << "\n";
}

void secondMode(){
    int N, Nmax = 1000000;
    float X1, X2, Mul;

    cout << "In this program will be integrate function y(x) = 0,5*sin(x)+x\n";

    cout << "Enter left and right boundaries of integration\n";
    cin >> X1 >> X2;

    cout << "Enter number of integration sections\n";
    cin >> N;

    cout << "Enter multiplier\n";
    cin >> Mul;

    cout << "Result of integration by the RIGHT RECTANGLE METHOD:\n";
    accIntegration(rightRectangle, X1, X2, N, Nmax, Mul);
    cout << "\n";

    cout << "Result of integration by the LEFT RECTANGLE METHOD:\n";
    accIntegration(leftRectangle, X1, X2, N, Nmax, Mul);
    cout << "\n";

    cout << "Result of integration by the TRAPEZOID METHOD:\n";
    accIntegration(Trapezoid, X1, X2, N, Nmax, Mul);
    cout << "\n";
}

void accIntegration(float integrMethod(float, float, int), float x1, float x2, int n, int Nmax, float Mul){
    float i1, i2, e;

    if (n < Nmax)
        i1 = integrMethod(x1, x2, n);
    else {
        cout << "Calculating error, n>Nmax\n";
        return;
    }

    n = n * Mul;

    if (n < Nmax)
        i2 = integrMethod(x1, x2, n);
    else {
        cout << "Calculating error, n>Nmax\n";
        return;
    }

    e = abs(i1-i2);

    if (e < 1 && n < Nmax){
        cout << "The value of the integral calculated up to e=1 is equal to " << i2 << "\n";
        return;
    }

    while (e >= 1 || n < Nmax){
        i1 = i2;
        n *= Mul;
        i2 = integrMethod(x1, x2, n);

        e = abs(i1-i2);

        if (e < 1 && n < Nmax){
            cout << "The value of the integral calculated up to e=1 is equal to " << i2 << "\n";
            return;
        }
    }

    cout << "Calculating error, n>Nmax\n";
}

//Вычисление шага интегрирования
float dxCalculator(float x1,float x2,int n){
    float res;
    res = (x2-x1)/n;

    return res;
}

//Вычисление текущего значения у
float yCurCalculator(float xCur){
    float yCur;
    yCur =  (sin(xCur) + xCur)/2;

    return yCur;
}

//Вычисление по методу левых прямоуглоьников
float leftRectangle(float x1, float x2, int n){
    float xCur = x1;
    float dx = dxCalculator(x1, x2, n);
    float res = 0;

    for (int i = 0; i < n-1; i++)
    {
        res += abs(yCurCalculator(xCur) * dx);
        xCur += dx;
    }

    res += abs(yCurCalculator(xCur) * (x2-xCur));

    return res;
}

//Вычисление по методу правых прямоуглоьников
float rightRectangle(float x1, float x2, int n){
    float xCur = x2;
    float dx = dxCalculator(x1, x2, n);
    float res = 0;

    for (int i = 0; i < n-1; i++)
    {
        res += abs(yCurCalculator(xCur) * dx);
        xCur -= dx;
    }

    res += abs(yCurCalculator(xCur) * (xCur-x1));

    return res;
}

//Вычисление по методу трапеций
float Trapezoid(float x1, float x2, int n){
    float dx = dxCalculator(x1, x2, n);
    float xCur = x1, xNext = x1 + dx;
    float res = 0;

    for (int i = 0; i < n-1; i++)
    {
        res += abs((yCurCalculator(xCur) + yCurCalculator(xNext))/2 * dx);
        xCur = xNext;
        xNext += dx;
    }

    res += abs((yCurCalculator(xCur) + yCurCalculator((x2-xCur)))/2 * (x2-xCur));

    return res;
}