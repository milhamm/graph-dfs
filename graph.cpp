#include "graph.h"

/*
    author : Muhammad Ilham Mubarak
*/

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
    if (firstNeigbour(P1) == NULL)
    {
        firstNeigbour(P1) = createNeighbour(value, weight);
    }
    else
    {
        addressNeighbour K = firstNeigbour(P1);
        addressNeighbour prevK = NULL;
        addressNeighbour E = createNeighbour(value, weight);

        if (weight <= weight(K))
        {
            next(E) = firstNeigbour(P1);
            firstNeigbour(P1) = E;
        }
        else
        {
            while (K != NULL && weight > weight(K))
            {
                prevK = K;
                K = next(K);
            }

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
    cout << "=== Print Graph ===" << endl;
    addressVertex V = first(G);
    if (V != NULL)
    {
        cout << "Print Format: " << endl;
        cout << "Node <Number> : [<Neighbour> (<Weight>)]" << endl;

        cout << endl
             << "Graph: " << endl;
        while (V != NULL)
        {
            cout << "Vertex " << value(V) << ": ";
            addressNeighbour P = firstNeigbour(V);
            while (P != NULL)
            {
                cout << "[" << value(P) << " (" << weight(P) << ")]"
                     << (next(P) == NULL ? "" : ", ");
                P = next(P);
            }
            cout << endl;
            V = next(V);
        }
    }
    else
    {
        cout << "Graph is Empty" << endl;
    }
}

void dfs_all(Graph G, addressVertex vertex, bool isVisited[])
{
    isVisited[value(vertex)] = true;

    cout << value(vertex) << " ";

    addressNeighbour P = firstNeigbour(vertex);
    while (P != NULL)
    {
        if (!isVisited[value(P)])
            dfs_all(G, findVertex(G, value(P)), isVisited);
        P = next(P);
    }
}

void dfs_find(Graph G, addressVertex vertex, bool isVisited[], int searchedVertex, bool &isFound)
{
    isVisited[value(vertex)] = true;
    isFound = value(vertex) == searchedVertex;

    cout << value(vertex) << " ";
    if (!isFound)
    {
        addressNeighbour P = firstNeigbour(vertex);
        while (P != NULL)
        {
            if (!isVisited[value(P)] && !isFound)
                dfs_find(G, findVertex(G, value(P)), isVisited, searchedVertex, isFound);
            P = next(P);
        }
    }
}

void dfs(Graph G, int initialVertex, bool isFindVertex)
{
    int N = G.numOfVertices;
    bool *isVisited = new bool[N];
    memset(isVisited, 0, N);

    if (!isFindVertex)
    {
        cout << "DFS : ";
        dfs_all(G, findVertex(G, initialVertex), isVisited);
    }
    else
    {
        cout << "Vertex to find: ";
        int searchedVertex;
        cin >> searchedVertex;
        bool isFound = false;

        addressVertex P = findVertex(G, searchedVertex);
        if (P != NULL)
        {
            cout << "DFS : ";
            dfs_find(G, findVertex(G, initialVertex), isVisited, searchedVertex, isFound);
        }
        else
        {
            cout << "Vertex does not exist";
        }
    }

    cout << endl;
}

void printCommand()
{
    cout << endl;
    cout << "======== Menu ========" << endl;
    cout << "[1] DFS From File" << endl;
    cout << "[2] Add A Vertex" << endl;
    cout << "[3] Add an Edge" << endl;
    cout << "[4] DFS to Visit All Vertices" << endl;
    cout << "[5] DFS to Find Vertex" << endl;
    cout << "[6] Print the Graph" << endl;
    cout << "[7] Reset the Graph" << endl;
    cout << "[0] Exit Program " << endl;
    cout << "Pick a menu : ";
}

void commandAddVertex(Graph &G)
{
    cout << "=== Add Vertex ===" << endl;
    cout << "What is the name of your vertex? (Use Number) : ";
    int vertex;
    cin >> vertex;

    addVertex(G, vertex);
    cout << "Vertex " << vertex << " has been added to the graph" << endl;
}

void commandAddEdge(Graph &G)
{
    cout << "=== Add Edge ===" << endl;
    int from, to, weight;
    cout << "From Vertex: ";
    cin >> from;
    cout << "To Vertex: ";
    cin >> to;
    cout << "Weight: ";
    cin >> weight;

    addEdge(G, from, to, weight);
    cout << "Edge From Vertex " << from << " to " << to << " with the weight of " << weight << endl;
}

void commandDFSAll(Graph G)
{
    cout << "=== DFS All ===" << endl;
    int initial;
    cout << "Initial Vertex: ";
    cin >> initial;
    dfs(G, initial, false);
}

void commandDFSFind(Graph G)
{
    cout << "=== DFS Find ===" << endl;
    int initial, to;
    cout << "Initial Vertex: ";
    cin >> initial;
    dfs(G, initial, true);
}

void commandInputFromFile()
{
    Graph G;
    createGraph(G);
    bool isSearch = false;

    cout << "[1] Run DFS to all Vertex (default)" << endl;
    cout << "[2] Run DFS to search Vertex" << endl;
    cout << "Pick a menu : ";
    int command;
    cin >> command;

    if (command == 2)
        isSearch = true;

    ifstream inFile;
    string filename = "./inputs/";

    char file;
    cout << "What File do you want to open? (1 - 3): ";
    cin >> file;

    filename = filename + file + ".in";
    inFile.open(filename);

    if (inFile)
    {
        int n;
        inFile >> n;
        while (n--)
        {
            int a, b, w;
            inFile >> a >> b >> w;
            addEdge(G, a, b, w);
        }

        int initialVertex;
        inFile >> initialVertex;
        inFile.close();

        dfs(G, initialVertex, isSearch);
    }
    else
    {
        cout << "The File Doesn't exist" << endl;
    }
}