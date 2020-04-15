#include "graph.h"

void puts(string s)
{
    cerr << s << endl;
}

void createGraph(Graph &G)
{
    first(G) = NULL;
    G.numOfVertices = 0;
}

addressVertex createVertex(int value)
{
    addressVertex P = new Vertex;
    value(P) = value;
    next(P) = NULL;
    firstNeigbour(P) = NULL;

    return P;
}

addressNeighbour createNeighbour(int value, int weight)
{
    addressNeighbour P = new Neighbour;
    value(P) = value;
    weight(P) = weight;
    next(P) = NULL;

    return P;
}

void addVertex(Graph &G, int value)
{
    if (first(G) == NULL)
    {
        first(G) = createVertex(value);
    }
    else
    {
        addressVertex P = first(G);
        while (next(P) != NULL)
            P = next(P);
        next(P) = createVertex(value);
    }

    G.numOfVertices++;
}

addressVertex findVertex(Graph G, int value)
{
    addressVertex P = first(G);

    while (P != NULL)
    {
        if (value(P) == value)
            return P;
        P = next(P);
    }

    return NULL;
}

void insertEdgeAscending(Graph &G, addressVertex P1, int value, int weight)
{
    if (firstNeigbour(P1) == NULL || weight < weight(firstNeigbour(P1)))
    {
        firstNeigbour(P1) = createNeighbour(value, weight);
    }
    else
    {
        addressNeighbour K = firstNeigbour(P1);
        addressNeighbour prevK = NULL;
        while (K != NULL && weight > weight(K))
        {
            prevK = K;
            K = next(K);
        }

        addressNeighbour E = createNeighbour(value, weight);

        if (next(prevK) == NULL || weight > weight(K))
        {
            next(prevK) = E;
        }
        else
        {
            next(E) = next(prevK);
            next(prevK) = E;
        }
    }
}

void addEdge(Graph &G, int V1, int V2, int weight)
{
    addressVertex P1 = findVertex(G, V1);
    addressVertex P2 = findVertex(G, V2);

    if (P1 == NULL)
    {
        addVertex(G, V1);
        P1 = findVertex(G, V1);
    }

    if (P2 == NULL)
    {
        addVertex(G, V2);
        P2 = findVertex(G, V2);
    }

    insertEdgeAscending(G, P1, V2, weight);
    insertEdgeAscending(G, P2, V1, weight);
}

void printGraph(Graph G)
{
    addressVertex V = first(G);
    while (V != NULL)
    {
        cout << value(V) << ": ";
        addressNeighbour P = firstNeigbour(V);
        while (P != NULL)
        {
            cout << "{" << value(P) << "," << weight(P) << "}"
                 << (next(P) == NULL ? "" : ", ");
            P = next(P);
        }
        cout << endl;
        V = next(V);
    }
}

void dfs_r(Graph G, addressVertex vertex, bool isVisited[])
{
    isVisited[value(vertex)] = true;
    cout << value(vertex) << " ";

    addressNeighbour P = firstNeigbour(vertex);
    while (P != NULL)
    {
        if (!isVisited[value(P)])
            dfs_r(G, findVertex(G, value(P)), isVisited);
        P = next(P);
    }
}

void dfs(Graph G, int initialVertex)
{
    int N = G.numOfVertices;
    bool *isVisited = new bool[N];
    memset(isVisited, 0, N);

    dfs_r(G, findVertex(G, initialVertex), isVisited);
    cout << endl;
}
