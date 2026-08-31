#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

char opStack[MAX];
int opTop = -1;

int valueStack[MAX];
int valueTop = -1;

void pushOperator(char ch)
{
    opStack[++opTop] = ch;
}

char popOperator()
{
    return opStack[opTop--];
}

void pushValue(int value)
{
    valueStack[++valueTop] = value;
}

int popValue()
{
    return valueStack[valueTop--];
}

int precedence(char op)
{
    if (op == '/' || op == '*')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}

int calculate(int a, int b, char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    int i, j;

    if (argc < 2)
    {
        printf("Please enter an arithmetic expression.\n");
        return 1;
    }

    for (i = 1; i < argc; i++)
    {
        j = 0;

        while (argv[i][j] != '\0')
        {
            char ch = argv[i][j];

            if (ch == ' ')
            {
                j++;
                continue;
            }


            if (isdigit(ch))
            {
                int number = 0;

                while (isdigit(argv[i][j]))
                {
                    number = number * 10 + (argv[i][j] - '0');
                    j++;
                }

                pushValue(number);
            }

            else if (ch == '(')
            {
                pushOperator(ch);
                j++;
            }

            else if (ch == ')')
            {
                while (opTop != -1 && opStack[opTop] != '(')
                {
                    char op = popOperator();

                    int b = popValue();
                    int a = popValue();

                    pushValue(calculate(a, b, op));
                }

                if (opTop != -1)
                    popOperator();

                j++;
            }

            else if (ch == '+' || ch == '-' ||
                     ch == '*' || ch == '/')
            {
                while (opTop != -1 &&
                       opStack[opTop] != '(' &&
                       precedence(opStack[opTop]) >= precedence(ch))
                {
                    char op = popOperator();

                    int b = popValue();
                    int a = popValue();

                    pushValue(calculate(a, b, op));
                }

                pushOperator(ch);
                j++;
            }

            else
            {
                printf("Invalid character: %c\n", ch);
                return 1;
            }
        }
    }

    while (opTop != -1)
    {
        char op = popOperator();

        int b = popValue();
        int a = popValue();

        pushValue(calculate(a, b, op));
    }

    printf("%d\n", popValue());

    return 0;
}