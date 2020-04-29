#include "graph.h"

/*
    Author : Muhammad Ilham Mubarak
    Class :  IF-43-INT - 1301194276
*/

int main()
{
    Graph G;
    createGraph(G);

    int command;
    do
    {
        printCommand();
        cin >> command;
        cout << endl;
        switch (command)
        {
        case 1:
            commandInputFromFile();
            break;
        case 2:
            commandAddVertex(G);
            break;
        case 3:
            commandAddEdge(G);
            break;
        case 4:
            commandDFSAll(G);
            break;
        case 6:
            printGraph(G);
            break;
        case 7:
            createGraph(G);
            break;
        case 0:
            cout << "Thank you for using this program\nMade By Muhammad Ilham Mubarak - IF-43-INT - 1301194276" << endl;
            break;
        default:
            cout << "Please input the valid number (0 ~ 9)" << endl;
            break;
        }
    } while (command != 0);

    return 0;
}