#include <stdio.h>

#define N 5

int graph[N][N] = {
    {0,1,1,0,0},
    {1,0,1,1,0},
    {1,1,0,1,0},
    {0,1,1,0,1},
    {0,0,0,1,0}
};

int selected[N], m;

int isClique(int v)
{
    int i;
    for(i=0;i<N;i++)
        if(selected[i] && !graph[v][i])
            return 0;
    return 1;
}

int clique(int v, int count)
{
    int i;

    if(count == m)
        return 1;

    if(v == N)
        return 0;

    for(i=v;i<N;i++) {
        if(isClique(i)) {
            selected[i] = 1;

            if(clique(i+1,count+1))
                return 1;

            selected[i] = 0;
        }
    }

    return 0;
}

int main()
{
    m = 3;

    if(clique(0,0))
        printf("Clique of size %d exists\n",m);
    else
        printf("Clique of size %d does not exist\n",m);

    return 0;
}