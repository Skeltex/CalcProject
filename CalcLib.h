#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <sstream>

#include <math.h>
#include <cmath>
#include <iomanip>
#include <Windows.h>

using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);


string get_str_pi() {
    ostringstream ost;
    ost << fixed << setprecision(15) << M_PI;

    return ost.str();
}

string get_str_e() {
    ostringstream ost;
    ost << fixed << setprecision(15) << M_E;

    return ost.str();
}

string pi = get_str_pi();
string e = get_str_e();

const short operators_count = 22;
string operators[operators_count] = { "+", "-", "*", "/", "^", "sqrt", "cbrt", "ln", "lg", "abs", "exp", 
    "sin", "cos", "tan", "ctg", "asin", "acos", "atan", "actg", "!", "%", "d" };

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isNumber(string c) {
    return isDigit(c[c.size() - 1]);
}

bool isTtrigonometricFunction(string c) {
    return c == "sin" || c == "cos" || c == "tan" || c == "ctg" ||
        c == "asin" || c == "acos" || c == "atan" || c == "actg";
}





bool isLeftUnaryOperator(string c) {
    return c == "!" || c == "%" || c == "d";
}

bool isRightUnaryOperator(string c) {
    return c == "sqrt" || c == "cbrt" || c == "ln" || c == "lg" || c == "abs" || c == "exp" || isTtrigonometricFunction(c);
}

bool isUnaryOperator(string c) {
    return isLeftUnaryOperator(c) || isRightUnaryOperator(c);
}

bool isBinaryOperator(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^";
}

bool isOperator(string c) {
    return isBinaryOperator(c) || isLeftUnaryOperator(c) || isRightUnaryOperator(c);
}



double string_to_double(string a) {
    return stod(a);
}

string double_to_string(double a) {
    ostringstream a_ostringstream;
    a_ostringstream << a;
    string str_a = a_ostringstream.str();
    return str_a;
}




short findMaxPriorityIndex(short* arr, short size) {
    short max = arr[0];
    short max_index = 0;
    for (int i = 1; i < size; ++i)
        if (arr[i] > max) {
            max = arr[i];
            max_index = i;
        }

    return max_index;
}

void removePriorityByIndex(short*& arr1, short& size, short index) {
    short* arr2 = new short[size - 1];
    short shift = 0;
    for (short i = 0; i < size - 1; ++i) {
        if (i == index)
            ++shift;
        arr2[i] = arr1[i + shift];
    }

    delete[] arr1;
    arr1 = arr2;

    --size;
}


short findMaxOperatorIndex(string* expression_array, short size, short max_priority_index) {
    short count = 0;
    for (short i = 0; i < size; ++i) {
        if (isOperator(expression_array[i]))
            ++count;
        if (count == max_priority_index + 1)
            return i;
    }
    return -1;
}



void findFirstOperand(string*& expression_arr, short& index, short& count_open_brackets, short& count_close_brackets, short direction) {
    index += direction;
    while (!isNumber(expression_arr[index])) {
        if (expression_arr[index] == "(")
            ++count_open_brackets;
        if (expression_arr[index] == ")")
            ++count_close_brackets;
        index += direction;
    }
}


void findTwoOperands(string* expression_arr, short size, short index, short& start_remove_index, short& end_remove_index, double& left_operand, double& right_operand) {
    short count_open_brackets = 0, count_close_brackets = 0, const_index = index;

    findFirstOperand(expression_arr, index, count_open_brackets, count_close_brackets, -1);

    left_operand = string_to_double(expression_arr[index]);
    start_remove_index = index;


    index = const_index;

    findFirstOperand(expression_arr, index, count_open_brackets, count_close_brackets, 1);

    right_operand = string_to_double(expression_arr[index]);
    end_remove_index = index;

    if ((count_open_brackets - count_close_brackets) > 0)
        end_remove_index += (count_open_brackets - count_close_brackets);
    else start_remove_index += (count_open_brackets - count_close_brackets);


    cout << "left_binary_operand = " << left_operand << ";   ";
    cout << "right_binary_operand = " << right_operand << '\n';

}


void findOneLeftOperand(string* expression_arr, short size, short index, short& start_remove_index, double& left_operand) {
    short count_open_brackets = 0, count_close_brackets = 0;

    findFirstOperand(expression_arr, index, count_open_brackets, count_close_brackets, -1);

    left_operand = string_to_double(expression_arr[index]);
    start_remove_index = index + (count_open_brackets - count_close_brackets);


    cout << "left_unary_operand = " << left_operand << '\n';
}


void findOneRightOperand(string* expression_arr, short size, short index, short& end_remove_index, double& right_operand) {
    short count_open_brackets = 0;
    short count_close_brackets = 0;

    findFirstOperand(expression_arr, index, count_open_brackets, count_close_brackets, 1);

    right_operand = string_to_double(expression_arr[index]);
    end_remove_index = index + (count_open_brackets - count_close_brackets);


    cout << "right_unary_operand = " << right_operand << '\n';
}



void result_replace(string*& expression_array1, short start_remove_index, short end_remove_index, double result, short& size1) {
    short size2 = size1 - (end_remove_index - start_remove_index);
    string* expression_array2 = new string[size2];


    string str_result = double_to_string(result);



    cout << "start_remove_index = " << start_remove_index << ";   ";
    cout << "end_remove_index = " << end_remove_index << '\n';

    for (short i = 0; i < start_remove_index; ++i)
        expression_array2[i] = expression_array1[i];

    expression_array2[start_remove_index] = str_result;

    for (short i = 0; i < size1 - 1 - end_remove_index; ++i)
        expression_array2[start_remove_index + 1 + i] = expression_array1[end_remove_index + 1 + i];

    delete[] expression_array1;
    size1 = size2;
    expression_array1 = expression_array2;
}


double simple_arithmetic_operation(double a, double b, string operator1) {
    if (operator1 == "+") return a + b;
    else if (operator1 == "-") return a - b;
    else if (operator1 == "*") return a * b;
    else if (operator1 == "/") return a / b;
    else if (operator1 == "^") return pow(a, b);
    return 0;
}

double simple_arithmetic_operation(double a, string operator1) {
    if (operator1 == "!") return tgamma(a + 1);
    else if (operator1 == "%") return a * 0.01;
    else if (operator1 == "d") return a * acos(-1.0) / 180;

    else if (operator1 == "sqrt") return sqrt(a);
    else if (operator1 == "cbrt") return cbrt(a);
    else if (operator1 == "ln") return log(a);
    else if (operator1 == "lg") return log10(a);
    else if (operator1 == "abs") return fabs(a);
    else if (operator1 == "exp") return exp(a);

    else if (operator1 == "sin") return sin(a);
    else if (operator1 == "cos") return cos(a);
    else if (operator1 == "tan") return tan(a);
    else if (operator1 == "ctg") return 1.0 / tan(a);

    else if (operator1 == "asin") return asin(a);
    else if (operator1 == "acos") return acos(a);
    else if (operator1 == "atan") return atan(a);
    else if (operator1 == "actg") return acos(-1.0) / 2 - atan(-a);
    return 0;
}




string getExpression() {
    string expression;
    cout << "Enter expression: ";
    cin >> expression;
    return expression;
}




bool checkingIn(string& expression, string*& expression_array, short& str_i, short& arr_i, string substring) {
    short size = substring.size();

    bool flag = false;
    for (short i = 0; i < size; i++)
        if (expression[str_i + i] == substring[i])
            flag = true;
        else
            return false;
    return flag;
}

void addToExpressionArray(string& expression, string*& expression_array, short& str_i, short& arr_i, string substring, string new_substring = " ") {
    if (new_substring == " ")
        new_substring = substring;
    expression_array[arr_i++] = new_substring;
    str_i += substring.size();
}



bool isNumberSimvol(string expression, short str_i) {
    return (((expression[str_i] == '-' && ((str_i == 0) || (expression[str_i - 1] != ')'
        && !isDigit(expression[str_i - 1])))) || isDigit(expression[str_i]) || expression[str_i] == '.'));
}



string* getExpressionArray(string expression, short expression_size, short& expression_array_size) {
    const short max_size = 200;
    string* expression_array = new string[max_size];

    short str_i = 0;
    short arr_i = 0;

    while (str_i < expression_size) {
        bool flag = false;
        while (isNumberSimvol(expression, str_i)) {
            flag = true;
            expression_array[arr_i] += expression[str_i++];
        }
        if (flag)
            ++arr_i;


        if (checkingIn(expression, expression_array, str_i, arr_i, "pi"))
            addToExpressionArray(expression, expression_array, str_i, arr_i, "pi", pi);

        else if (checkingIn(expression, expression_array, str_i, arr_i, "e"))
            addToExpressionArray(expression, expression_array, str_i, arr_i, e);

        else if (checkingIn(expression, expression_array, str_i, arr_i, "("))
            addToExpressionArray(expression, expression_array, str_i, arr_i, "(");

        else if (checkingIn(expression, expression_array, str_i, arr_i, ")"))
            addToExpressionArray(expression, expression_array, str_i, arr_i, ")");
        else {
            for (short i = 0; i < operators_count; ++i) {
                if (checkingIn(expression, expression_array, str_i, arr_i, operators[i]))
                    addToExpressionArray(expression, expression_array, str_i, arr_i, operators[i]);
                if (str_i >= expression_size)
                    break;
            }
        }
    }
    expression_array_size = arr_i;
    return expression_array;
}

void printExpressionArray(string* expression_array, short expression_array_size) {
    for (short i = 0; i < expression_array_size; ++i) {
        cout << "[";
        SetConsoleTextAttribute(handle, 4);
        cout << expression_array[i];
        SetConsoleTextAttribute(handle, 7);
        cout << "] ";
    }
    cout << '\n';
}


void printPriorityArray(short* operators_priority, short size) {
    cout << "Priorities: ";
    SetConsoleTextAttribute(handle, 3);
    for (short i = 0; i < size; i++)
        cout << operators_priority[i] << ' ';
    SetConsoleTextAttribute(handle, 7);
    cout << endl;
}

void printResult(double result) {
    cout << "Action result: ";
    SetConsoleTextAttribute(handle, 2);
    cout << result;
    SetConsoleTextAttribute(handle, 7);
    cout << '\n';
}



short operatorsCounter(string* expression_array, short size) {
    short count = 0;
    for (short i = 0; i < size; ++i)
        if (isOperator(expression_array[i]))
            ++count;
    return count;
}

short* getOperatorsPriority(string* expression, short size) {
    short* operators_priority = new short[size];
    short last_index = 0;
    short priority_add = 0;
    for (short i = 0; i < size; i++)
        if (expression[i] == "(")
            priority_add += 3;
        else if (expression[i] == ")")
            priority_add -= 3;
        else if (expression[i] == "+" || expression[i] == "-")
            operators_priority[last_index++] = 1 + priority_add;
        else if (expression[i] == "*" || expression[i] == "/")
            operators_priority[last_index++] = 2 + priority_add;
        else if (expression[i] == "%" || expression[i] == "!" || expression[i] == "d" ||
            expression[i] == "^" || expression[i] == "sqrt" || expression[i] == "cbrt"
            || expression[i] == "ln" || expression[i] == "lg" || expression[i] == "abs" || expression[i] == "exp"
            || isTtrigonometricFunction(expression[i]))
            operators_priority[last_index++] = 3 + priority_add;
    return operators_priority;
}


string solveExpression(string expression, short expression_size) {
    short expression_array_size = 0;
    string* expression_array = getExpressionArray(expression, expression_size, expression_array_size);

    short operators_quantity = operatorsCounter(expression_array, expression_array_size);
    short* operators_priority = getOperatorsPriority(expression_array, expression_array_size);


    while (operators_quantity > 0) {
        printExpressionArray(expression_array, expression_array_size);
        printPriorityArray(operators_priority, operators_quantity);

        short max_priority_index = findMaxPriorityIndex(operators_priority, operators_quantity);
        short max_operator_index = findMaxOperatorIndex(expression_array, expression_array_size, max_priority_index);

        short start_remove_index, end_remove_index;
        double left_operand, right_operand, result;

        string error;

        if (isLeftUnaryOperator(expression_array[max_operator_index])) {
            end_remove_index = max_operator_index;
            findOneLeftOperand(expression_array, expression_array_size, max_operator_index, start_remove_index, left_operand);
            result = simple_arithmetic_operation(left_operand, expression_array[max_operator_index]);
        }
        else if (isRightUnaryOperator(expression_array[max_operator_index])) {
            start_remove_index = max_operator_index;
            findOneRightOperand(expression_array, expression_array_size, max_operator_index, end_remove_index, right_operand);
            result = simple_arithmetic_operation(right_operand, expression_array[max_operator_index]);
        }
        else if (isBinaryOperator(expression_array[max_operator_index])) {
            findTwoOperands(expression_array, expression_array_size, max_operator_index, start_remove_index, end_remove_index, left_operand, right_operand);
            result = simple_arithmetic_operation(left_operand, right_operand, expression_array[max_operator_index]);
        }

        printResult(result);

        result_replace(expression_array, start_remove_index, end_remove_index, result, expression_array_size);
        removePriorityByIndex(operators_priority, operators_quantity, max_priority_index);
    }

    cout << "\nFinal array: ";
    printExpressionArray(expression_array, expression_array_size);

    return expression_array[expression_array_size / 2];
}

void printResult(string result)
{
    cout << "Result: ";
    SetConsoleTextAttribute(handle, 5);
    cout << result << "\n\n";
    SetConsoleTextAttribute(handle, 7);
}
