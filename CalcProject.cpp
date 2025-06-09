#include <iostream>
#include "CalcLib.h"
#include <string>

using namespace std;

int main() {
    string expression = getExpression();
    string result = solveExpression(expression, size(expression));

    printResult(result);
}
