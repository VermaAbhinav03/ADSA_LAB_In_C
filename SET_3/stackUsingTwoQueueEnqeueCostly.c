#include <stdio.h>
#define MAX 100

int q1[MAX], q2[MAX];
int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

/* Enqueue into a queue */
void enqueue(int q[], int *rear, int value)
{
    q[++(*rear)] = value;
}

/* Dequeue from a queue */
int dequeue(int q[], int *front, int rear)
{
    if (*front > rear)
        return -1;

    return q[(*front)++];
}

/* Push operation - Costly Enqueue */
void push(int value)
{
    int x;

    /* Add new element to q2 */
    enqueue(q2, &rear2, value);

    /* Move all elements from q1 to q2 */
    while (front1 <= rear1)
    {
        x = dequeue(q1, &front1, rear1);
        enqueue(q2, &rear2, x);
    }

    /* Swap q1 and q2 */
    int temp[MAX];
    int tempFront, tempRear;

    for (int i = 0; i <= rear2; i++)
        temp[i] = q2[i];

    tempFront = front2;
    tempRear = rear2;

    for (int i = 0; i <= rear1; i++)
        q2[i] = q1[i];

    front2 = front1;
    rear2 = rear1;

    for (int i = 0; i <= tempRear; i++)
        q1[i] = temp[i];

    front1 = tempFront;
    rear1 = tempRear;
}

/* Pop operation */
int pop()
{
    if (front1 > rear1)
    {
        printf("Stack Underflow\n");
        return -1;
    }

    return dequeue(q1, &front1, rear1);
}

void display()
{
    if (front1 > rear1)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");
    for (int i = front1; i <= rear1; i++)
        printf("%d ", q1[i]);

    printf("\n");
}

int main()
{
    push(10);
    push(20);
    push(30);
    push(40);

    display();

    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());

    display();

    return 0;
}
