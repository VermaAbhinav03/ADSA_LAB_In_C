#include <stdio.h>

#define SIZE 5

int stack1[SIZE], stack2[SIZE];
int top1 = -1, top2 = -1;

/* Push into Stack 1 */
void push1(int value)
{
    stack1[++top1] = value;
}

/* Pop from Stack 1 */
int pop1()
{
    return stack1[top1--];
}

/* Push into Stack 2 */
void push2(int value)
{
    stack2[++top2] = value;
}

/* Pop from Stack 2 */
int pop2()
{
    return stack2[top2--];
}

/* Enqueue - Costly */
void enqueue(int value)
{
    /* Move all elements to Stack 2 */
    while (top1 != -1)
    {
        push2(pop1());
    }

    /* Add new element to Stack 1 */
    push1(value);

    /* Move everything back to Stack 1 */
    while (top2 != -1)
    {
        push1(pop2());
    }

    printf("%d inserted\n", value);
}

/* Dequeue - Easy */
void dequeue()
{
    if (top1 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    printf("%d deleted\n", pop1());
}

/* Display */
void display()
{
    int i;

    if (top1 == -1)
    {
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue: ");

    for (i = top1; i >= 0; i--)
    {
        printf("%d ", stack1[i]);
    }

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    dequeue();

    display();

    enqueue(40);

    display();

    dequeue();

    display();

    return 0;
}
