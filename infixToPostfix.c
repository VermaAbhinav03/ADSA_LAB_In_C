#include <stdio.h>
#include<ctype.h>

char stack[100];
int top = -1;

void push(char c){
    stack[++top] = c;
}

char pop(){
    return stack[top--];
}


int priority(char ch){
    if (ch == '*' || ch == '/')
    {
        return 2;
    }else if(ch == '+' || ch =='-'){
        return 1;
    }
    return 0;
}


void infixTopostfix(char infix[],char postfix[]){
   int i = 0;
   int j = 0;
   char ch;
   for(int i = 0 ; infix[i]!= '\0';i++){
    ch = infix[i];
    if(ch >= '0' && ch <= '9'){
        postfix[j++] = ch;
    }
    else if(ch == '('){
        push(ch);
    }
    else if(ch ==')'){
        while(stack[top] != '('){
            postfix[j++] = pop();
        }

        pop();
    }else{
        while(top != -1 && stack[top] != '(' && priority(stack[top]) >= priority(ch) ){
            postfix[j++] = pop();
        }

        push(ch);
    }
    
   }
    while (top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

int main(){
   char infix[100], postfix[100];

    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixTopostfix(infix,postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}