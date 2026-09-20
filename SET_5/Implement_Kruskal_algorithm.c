#include <stdio.h>
#include <stdlib.h>

// Structure for an edge
struct Edge
{
    int src;
    int dest;
    int weight;
};

// Find the parent of a vertex
int find(int parent[], int vertex)
{
    if (parent[vertex] == vertex)
        return vertex;

    return find(parent, parent[vertex]);
}

// Join two sets
void unionSets(int parent[], int rank[], int x, int y)
{
    int rootX = find(parent, x);
    int rootY = find(parent, y);

    // If they are already in the same set,
    // joining them would create a cycle
    if (rootX == rootY)
        return;

    // Attach smaller tree under larger tree
    if (rank[rootX] < rank[rootY])
    {
        parent[rootX] = rootY;
    }
    else if (rank[rootX] > rank[rootY])
    {
        parent[rootY] = rootX;
    }
    else
    {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Compare two edges for sorting
int compareEdges(const void *a, const void *b)
{
    struct Edge *edge1 = (struct Edge *)a;
    struct Edge *edge2 = (struct Edge *)b;

    return edge1->weight - edge2->weight;
}

int main()
{
    int V = 4;
    int E = 5;

    // List of all edges
    struct Edge edges[5] =
    {
        {0, 1, 2},
        {0, 2, 6},
        {0, 3, 3},
        {1, 3, 5},
        {2, 3, 1}
    };

    // Sort edges by weight
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    // Parent and rank arrays for Union-Find
    int parent[V];
    int rank[V];

    // Initially every vertex is its own set
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int mstEdges = 0;
    int totalCost = 0;

    printf("Edges in Minimum Spanning Tree:\n");

    // Process edges in sorted order
    for (int i = 0; i < E && mstEdges < V - 1; i++)
    {
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;

        // Find the sets containing src and dest
        int rootSrc = find(parent, src);
        int rootDest = find(parent, dest);

        // If roots are different, no cycle is formed
        if (rootSrc != rootDest)
        {
            printf("%d - %d : %d\n", src, dest, weight);

            totalCost += weight;

            unionSets(parent, rank, rootSrc, rootDest);

            mstEdges++;
        }
    }

    printf("Total cost of MST = %d\n", totalCost);

    return 0;
}