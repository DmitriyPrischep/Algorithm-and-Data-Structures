#include <iostream>
#include <queue>
#include "igraph.h"
#include "clistgraph.h"
#include "cmatrixgraph.h"
#include "carcgraph.h"
#include "csetgraph.h"

using namespace std;

void BFS(const IGraph* graph, int vertex, void (*visit)(int))
{
    vector<bool> isQueued(graph->VerticesCount(), false);
    queue<int> greyVertices;
    isQueued[vertex] = true;
    greyVertices.push(vertex);
    while( !greyVertices.empty() ){
        int currentVertex = greyVertices.front();
        visit(currentVertex);
        greyVertices.pop();
        const vector<int>& outVertices = graph->GetNextVertices(currentVertex);
        for(size_t i = 0; i < outVertices.size(); i++){
            if(!isQueued[outVertices[i]]){
                isQueued[outVertices[i]] = true;
                greyVertices.push(outVertices[i]);
            }
        }
    }
}

int main()
{
    IGraph* graph = new CListGraph(5);
    IGraph* graph1 = new CMatrixGraph(5);
    IGraph* graph2 = new CArcGraph(5);
    IGraph* graph3 = new CSetGraph(5);
    graph->AddEdge(0, 2);
    graph->AddEdge(0, 3);
    graph->AddEdge(1, 0);
    graph->AddEdge(1, 3);
    graph->AddEdge(2, 1);
    graph->AddEdge(2, 4);
    graph->AddEdge(3, 4);
    BFS(graph, 1, [](int vertex){cout << vertex << " ";});
    std::cout << std::endl;

    graph1->AddEdge(0, 2);
    graph1->AddEdge(0, 3);
    graph1->AddEdge(1, 0);
    graph1->AddEdge(1, 3);
    graph1->AddEdge(2, 1);
    graph1->AddEdge(2, 4);
    graph1->AddEdge(3, 4);
    BFS(graph1, 1, [](int vertex){cout << vertex << " ";});
    std::cout << std::endl;

    graph2->AddEdge(0, 2);
    graph2->AddEdge(0, 3);
    graph2->AddEdge(1, 0);
    graph2->AddEdge(1, 3);
    graph2->AddEdge(2, 1);
    graph2->AddEdge(2, 4);
    graph2->AddEdge(3, 4);
    BFS(graph2, 1, [](int vertex){cout << vertex << " ";});
    std::cout << std::endl;

    graph3->AddEdge(0, 2);
    graph3->AddEdge(0, 3);
    graph3->AddEdge(1, 0);
    graph3->AddEdge(1, 3);
    graph3->AddEdge(2, 1);
    graph3->AddEdge(2, 4);
    graph3->AddEdge(3, 4);
    BFS(graph3, 1, [](int vertex){cout << vertex << " ";});
    std::cout << std::endl;
    return 0;
}
