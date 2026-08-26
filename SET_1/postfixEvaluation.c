#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

// Stack for integer values
int valStack[MAX];
int valTop = -1;
void pushVal(int val) { valStack[++valTop] = val; }
int popVal() { return valStack[valTop--]; }

// Stack for operators
char opStack[MAX];
int opTop = -1;
void pushOp(char op) { opStack[++opTop] = op; }
char popOp() { return opStack[opTop--]; }
char peekOp() { return opStack[opTop]; }
int isOpEmpty() { return opTop == -1; }

// Function to check operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Perform basic arithmetic
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// Function to compute the expression
int evaluate(char* exp) {
    for (int i = 0; exp[i] != '\0'; i++) {
        if (isspace(exp[i])) continue;

        // If number, extract full multi-digit value and push to value stack
        if (isdigit(exp[i])) {
            int val = 0;
            while (isdigit(exp[i])) {
                val = (val * 10) + (exp[i] - '0');
                i++;
            }
            pushVal(val);
            i--; // Adjust index after while loop
        }
        else if (exp[i] == '(') {
            pushOp(exp[i]);
        }
        else if (exp[i] == ')') {
            while (!isOpEmpty() && peekOp() != '(') {
                int val2 = popVal();
                int val1 = popVal();
                char op = popOp();
                pushVal(applyOp(val1, val2, op));
            }
            popOp(); // Remove '('
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            while (!isOpEmpty() && precedence(peekOp()) >= precedence(exp[i])) {
                int val2 = popVal();
                int val1 = popVal();
                char op = popOp();
                pushVal(applyOp(val1, val2, op));
            }
            pushOp(exp[i]);
        }
    }

    // Process any remaining operations
    while (!isOpEmpty()) {
        int val2 = popVal();
        int val1 = popVal();
        char op = popOp();
        pushVal(applyOp(val1, val2, op));
    }

    return popVal();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"expression\"\n", argv[0]);
        return 1;
    }

    // Combine command line arguments into one string
    char expression[MAX] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expression, argv[i]);
    }

    int result = evaluate(expression);
    printf("%d\n", result);

    return 0;
}