#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

#if !defined(GRAPH_H)
#define GRAPH_H

#define first(P) (P).first
#define next(P) (P)->next
#define firstNeigbour(P) (P)->firstNeighbour

#define weight(P) (P)->weight
#define value(P) (P)->value

typedef struct Vertex *addressVertex;
typedef struct Neighbour *addressNeighbour;

struct Vertex
{
    int value;
    addressVertex next;
    addressNeighbour firstNeighbour;
};

struct Neighbour
{
    int value;
    int weight;
    addressNeighbour next;
};

struct Graph
{
    addressVertex first;
    int numOfVertices;
};

void createGraph(Graph &G);
addressVertex createVertex(int value);
addressNeighbour createNeighbour(int value, int weight);

void addVertex(Graph &G, int value);
void addEdge(Graph &G, int V1, int V2, int weight);
void printGraph(Graph G);
void dfs(Graph G, int initialVertex, bool isFindVertex);

void printCommand();
void commandAddVertex(Graph &G);
void commandAddEdge(Graph &G);
void commandDFSAll(Graph G);
void commandInputFromFile();

#endif // GRAPH_H
