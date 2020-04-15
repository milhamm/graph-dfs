#include "graph.h"

int main()
{
    Graph G;
    createGraph(G);

    // addEdge(G, 0, 1, 6);
    // addEdge(G, 0, 2, 1);
    // addEdge(G, 1, 2, 2);
    // addEdge(G, 1, 3, 3);
    // addEdge(G, 1, 4, 1);
    // addEdge(G, 2, 3, 8);
    // addEdge(G, 3, 4, 6);

    addEdge(G, 0, 1, 7);
    addEdge(G, 0, 4, 8);
    addEdge(G, 0, 3, 3);
    addEdge(G, 1, 2, 1);
    addEdge(G, 1, 3, 4);
    addEdge(G, 2, 3, 2);
    addEdge(G, 3, 4, 3);

    // printGraph(G);

    dfs(G, 0);

    return 0;
}