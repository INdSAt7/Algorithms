#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using namespace std;

int precedence(char op);
void infixToPostfix(string expression, string tokens[], int& count);
bool parenthesesCheck(string expression);
bool isNumber(string str);
double calculation(string tokens[], int len, bool &success);
void firstMode();
void secondMode();

class Stack {
private:
    int capacity;
    int size;
    string* elements;

public:
    Stack(int capacity) : capacity(capacity), size(0) {
        elements = new string[capacity];
    }

    ~Stack() {
        delete[] elements;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    string top() const {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[size - 1];
    }

    string pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return elements[--size];
    }

    void push(string value) {
        if (isFull()) {
            throw std::out_of_range("Stack is full");
        }
        elements[size++] = value;
    }
};

class Queue {
private:
    int capacity;
    int size;
    string* elements;
    int front;
    int rear;

public:
    Queue(int capacity) : capacity(capacity), size(0), front(0), rear(-1) {
        elements = new string[capacity];
    }

    ~Queue() {
        delete[] elements;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == capacity;
    }

    string frontElement() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return elements[front];
    }

    string dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        string value = elements[front];
        front = (front + 1) % capacity;
        size--;
        return value;
    }

    void enqueue(string value) {
        if (isFull()) {
            throw std::out_of_range("Queue is full");
        }
        rear = (rear + 1) % capacity;
        elements[rear] = value;
        size++;
    }
};

Stack operatorStack(100);
Queue operatorQueue(100);

int main() {
    int mode;
    printf("Enter the program mode:\n"
           "1 - Calculating of arithmetic expression\n"
           "2 - Researching of a function by points\n");

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

int precedence(char op) {
    if (op == 's' || op == 'c') {
        return 4;
    } else if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return -1;
    }
}

void infixToPostfix(string expression, string tokens[], int& count) {
    count = 0;
    Stack operatorStack(100);
    bool unary;

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        unary = expression[i] == '-' && ((i > 1 && expression[i - 1] == '(') || i == 0);

        if (isdigit(c) || c == 'x' || (isdigit(expression[i - 1]) && (c == '.' || c == ',') && i > 1)) {
            string operand;

            while (i < expression.length() && (isdigit(c) || c == 'x' || (isdigit(expression[i - 1]) && c == '.' && i > 1))) {
                operand += expression[i++];
                c = expression[i];
            }

            i--;
            tokens[count++] = operand;

        } else if (c == '(') {
            operatorStack.push(string(1, c));

        } else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.top() != "(") {
                tokens[count++] = operatorStack.top();
                operatorStack.pop();
            }

            operatorStack.pop();

        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (unary && (c == '-')) {
                tokens[count++] = "0";
            }

            while (!operatorStack.isEmpty() && precedence(c) <= precedence(operatorStack.top()[0])) {
                tokens[count++] = operatorStack.top();
                operatorStack.pop();
            }

            operatorStack.push(string(1, c));

        } else if (c == 's' || c == 'c') {
            string trigOperator;

            while (i < expression.length() && expression[i] != '(') {
                trigOperator += expression[i++];
            }

            i--;
            operatorStack.push(trigOperator);
        }
    }

    while (!operatorStack.isEmpty()) {
        tokens[count++] = operatorStack.top();
        operatorStack.pop();
    }
}

bool parenthesesCheck(string expression) {
    int i = 0, counter = 0;

    while (expression[i] != '\0') {

        if (expression[i] == '(') {
            counter++;
        } else if (expression[i] == ')') {
            counter--;
        }
        i++;
    }

    return counter == 0;
}

bool isNumber(string str) {
    bool floatFlag = false;

    for (int i = 0; i < str.length(); i++) {

        if (str[i] == '-' && (i != 0 || str.length() == 1)) {
            return false;
        } else if (str[i] == '.') {
            if (floatFlag) {
                return false;
            } else {
                floatFlag = true;
            }
        } else if (!isdigit(str[i]) && str[i] != '-' && str[i] != '.') {
            return false;
        }
    }

    return true;
}

double calculation(string tokens[], int len, bool &success) {
    success = true;
    int counter = 0;
    double res = 0;

    string arg1, arg2;
    Stack calculatingStack(len); // Использование вашего класса Stack

    for (int i = 0; i < len; i++) {
        if (!success)
            break;

        if (isNumber(tokens[i])) {
            calculatingStack.push(tokens[i]);
            counter++;
        } else if ((tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" ||
                    tokens[i] == "^" || tokens[i] == "/") && counter > 1) {
            arg2 = calculatingStack.top();
            calculatingStack.pop();
            counter--;

            arg1 = calculatingStack.top();
            calculatingStack.pop();
            counter--;

            if (isNumber(arg1) && isNumber(arg2)) {
                switch (int(tokens[i][0])) {
                    case '-':
                        calculatingStack.push(to_string(stod(arg1) - stod(arg2)));
                        counter++;
                        break;
                    case '+':
                        calculatingStack.push(to_string(stod(arg1) + stod(arg2)));
                        counter++;
                        break;
                    case '*':
                        calculatingStack.push(to_string(stod(arg1) * stod(arg2)));
                        counter++;
                        break;
                    case '/':
                        if (stod(arg2) != 0) {
                            calculatingStack.push(to_string(stod(arg1) / stod(arg2)));
                            counter++;
                            break;
                        } else {
                            success = false;
                            break;
                        }
                    case '^':
                        calculatingStack.push(to_string(pow(stod(arg1), stod(arg2))));
                        counter++;
                        break;
                }
            } else {
                success = false;
                cout << "Error during calculation, invalid operands for arithmetic operation" << endl;
            }
        } else if ((tokens[i] == "sin" || tokens[i] == "cos") && counter > 0) {
            arg1 = calculatingStack.top();
            calculatingStack.pop();
            counter--;

            if (tokens[i] == "sin") {
                calculatingStack.push(to_string(sin(stod(arg1))));
                counter++;
            } else if (tokens[i] == "cos") {
                calculatingStack.push(to_string(cos(stod(arg1))));
                counter++;
            }
        } else {
            success = false;
        }
    }

    if (success) {
        res = stod(calculatingStack.top());
        calculatingStack.pop();
        return res;
    } else {
        return 0;
    }
}

void firstMode(){
    string expression = "1/(x-1)";
    string tokens[expression.length()];
    int count;
    bool success = true;
    int x;
    double res;
    bool fl = true;

    if (parenthesesCheck(expression)) {
        infixToPostfix(expression, tokens, count);

        cout << "Postfix expression tokens:" << endl;
        for (int i = 0; i < count; ++i) {
            cout << tokens[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < count; i++) {
            if (tokens[i] == "x" && fl) {
                cout << "Enter integer x \n";
                cin >> x;
                tokens[i] = to_string(x);
                fl = false;
            } else if (tokens[i] == "x") {
                tokens[i] = to_string(x);
            }
        }

        res = calculation(tokens, count, success);

        if (success) {
            cout << res << '\n';
        }
        else
            cout << "Error during calculating";

    } else {
        cout << "Incorrect placement of parentheses in the expression" << endl;
    }
}

void secondMode(){
    string expression;
    float Xmin, Xmax, step, Xcur;
    double res;
    int count;
    bool success = true;

    cout << "Enter expression to research\n";
    cin >> expression;

    string *tokens = new string[expression.length()];
    string *tokensCopy = new string[expression.length()];

    cout << "Enter left and right borders\n";
    cin >> Xmin >> Xmax;

    cout << "Enter step\n";
    cin >> step;

    if (parenthesesCheck(expression)) {
        infixToPostfix(expression, tokens, count);

        cout << endl;

        Xcur = Xmin;

        cout << 'x' << '\t' << "f(x)" << '\n';

        while (Xcur < Xmax){
            for (int i = 0; i < count; i++) {
                if (tokens[i] == "x")
                    tokensCopy[i] = to_string(Xcur);
                else
                    tokensCopy[i] = tokens[i];
            }
            res = calculation(tokensCopy, count, success);

            if (success) {
                cout << Xcur << "\t" << res << '\n';
            }
            else
                cout << Xcur << "\t" << '-' << '\n';

            success = true;

            Xcur += step;
        }

        Xcur = Xmax;

        for (int i = 0; i < count; i++) {
            if (tokens[i] == "x")
                tokensCopy[i] = to_string(Xcur);
            else
                tokensCopy[i] = tokens[i];
        }

        if (success) {
            res = calculation(tokensCopy, count, success);
            cout << Xcur << "\t" << res << '\n';
        }
        else
            cout << Xcur << "\t" << '-' << '\n';

    } else
        cout << "Incorrect placement of parentheses in the expression" << endl;

}