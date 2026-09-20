#include <stdio.h>

#define N 5

int graph[N][N] = {
    {0,1,0,1,1},
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1},
    {1,1,0,1,0}
};

int path[N];

int safe(int v, int pos)
{
    int i;

    if(!graph[path[pos-1]][v])
        return 0;

    for(i=0;i<pos;i++)
        if(path[i] == v)
            return 0;

    return 1;
}

int hamiltonian(int pos)
{
    int v;

    if(pos == N)
        return graph[path[N-1]][path[0]];

    for(v=1;v<N;v++) {
        if(safe(v,pos)) {
            path[pos] = v;

            if(hamiltonian(pos+1))
                return 1;

            path[pos] = -1;
        }
    }

    return 0;
}

int main()
{
    int i;

    for(i=0;i<N;i++)
        path[i] = -1;

    path[0] = 0;

    if(hamiltonian(1)) {
        printf("Hamiltonian Cycle exists:\n");

        for(i=0;i<N;i++)
            printf("%d -> ",path[i]);

        printf("%d\n",path[0]);
    }
    else
        printf("Hamiltonian Cycle does not exist\n");

    return 0;
}