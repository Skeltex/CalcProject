#include <iostream>
#include "CalcLib.h"
#include <string>

using namespace std;

int main()
{

    string expression = getExpression();

    short expression_size = size(expression);

    string result = solveExpression(expression, expression_size);


    printResult(result);


    return 0;
}