#include <stdio.h>

#define N 5

int d[N][N] = {          // Directed graph for SCC
    {0,1,0,0,0},
    {0,0,1,0,0},
    {1,0,0,1,0},
    {0,0,0,0,1},
    {0,0,1,0,0}
};

int g[N][N] = {          // Undirected graph
    {0,1,1,0,0},
    {1,0,1,1,0},
    {1,1,0,0,0},
    {0,1,0,0,1},
    {0,0,0,1,0}
};

int vis[N], disc[N], low[N], parent[N], ap[N], time;
int stackU[20], stackV[20], top = -1;

/* SCC */

void dfs1(int u, int *order, int *k)
{
    int v;
    vis[u] = 1;

    for(v=0; v<N; v++)
        if(d[u][v] && !vis[v])
            dfs1(v,order,k);

    order[(*k)++] = u;
}

void dfs2(int u)
{
    int v;
    vis[u] = 1;
    printf("%d ",u);

    for(v=0; v<N; v++)
        if(d[v][u] && !vis[v])
            dfs2(v);
}

void SCC()
{
    int order[N], k=0, i;

    for(i=0;i<N;i++) vis[i]=0;
    for(i=0;i<N;i++)
        if(!vis[i]) dfs1(i,order,&k);

    for(i=0;i<N;i++) vis[i]=0;

    printf("SCCs:\n");
    for(i=k-1;i>=0;i--)
        if(!vis[order[i]]) {
            dfs2(order[i]);
            printf("\n");
        }
}

/* BCC + AP + Bridge */

void printBCC(int u,int v)
{
    printf("BCC: ");

    while(top>=0) {
        printf("(%d-%d) ",stackU[top],stackV[top]);

        if(stackU[top]==u && stackV[top]==v) {
            top--;
            break;
        }
        top--;
    }
    printf("\n");
}

int min(int a,int b)
{
    return a<b?a:b;
}

void DFS(int u)
{
    int v,child=0;

    disc[u]=low[u]=++time;

    for(v=0;v<N;v++) {
        if(!g[u][v]) continue;

        if(!disc[v]) {
            child++;
            parent[v]=u;

            stackU[++top]=u;
            stackV[top]=v;

            DFS(v);

            low[u]=min(low[u],low[v]);

            if((parent[u]==-1 && child>1) ||
               (parent[u]!=-1 && low[v]>=disc[u]))
                ap[u]=1;

            if(low[v]>=disc[u])
                printBCC(u,v);

            if(low[v]>disc[u])
                printf("Bridge: %d-%d\n",u,v);
        }
        else if(v!=parent[u] && disc[v]<disc[u]) {
            stackU[++top]=u;
            stackV[top]=v;
            low[u]=min(low[u],disc[v]);
        }
    }
}

void BCC_AP_Bridge()
{
    int i;

    for(i=0;i<N;i++) {
        disc[i]=low[i]=0;
        parent[i]=-1;
        ap[i]=0;
    }

    time=0;

    for(i=0;i<N;i++)
        if(!disc[i])
            DFS(i);

    printf("Articulation Points: ");
    for(i=0;i<N;i++)
        if(ap[i]) printf("%d ",i);
    printf("\n");
}

int main()
{
    SCC();

    printf("\nBiconnected Components:\n");
    BCC_AP_Bridge();

    return 0;
}