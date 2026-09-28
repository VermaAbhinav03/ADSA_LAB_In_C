#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x, y;
};

struct Point p[100], hull[100];
int n, top = -1;

int cross(struct Point a, struct Point b, struct Point c)
{
    return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

int cmp(const void *a, const void *b)
{
    struct Point p1 = *(struct Point *)a;
    struct Point p2 = *(struct Point *)b;
    return (p1.x != p2.x) ? p1.x-p2.x : p1.y-p2.y;
}

int main()
{
    int i;
    printf("Enter number of points: ");
    scanf("%d", &n);

    printf("Enter coordinates (x y):\n");
    for (i = 0; i < n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);

    qsort(p, n, sizeof(struct Point), cmp);

    for (i = 0; i < n; i++) {
        while (top >= 1 &&
               cross(hull[top-1], hull[top], p[i]) <= 0)
            top--;
        hull[++top] = p[i];
    }

    int lower = top;
    for (i = n-2; i >= 0; i--) {
        while (top > lower &&
               cross(hull[top-1], hull[top], p[i]) <= 0)
            top--;
        hull[++top] = p[i];
    }

    printf("Convex Hull points:\n");
    for (i = 0; i < top; i++)
        printf("(%d, %d)\n", hull[i].x, hull[i].y);

    return 0;
}