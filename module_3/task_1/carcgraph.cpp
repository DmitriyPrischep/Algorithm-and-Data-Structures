#include "carcgraph.h"
#include <assert.h>

CArcGraph::CArcGraph(int verticesCount)
{
    assert(verticesCount > 0);
    countVertices = verticesCount;
}

CArcGraph::CArcGraph(const IGraph *graph)
{
    assert(graph != nullptr);
    for(size_t vertice = 0; vertice < (size_t)graph->VerticesCount(); vertice++){
//        std::vector<int> next_vertices = graph->GetNextVertices(vertice);
        for(auto v : graph->GetNextVertices(vertice)){
            AddEdge(vertice, v);
        }
    }
}

void CArcGraph::AddEdge(int from, int to)
{
    assert(from >= 0 && from < (int)countVertices);
    assert(to >= 0 && to < (int)countVertices);
    adjacencyPairs.push_back(std::pair<int, int>(from, to));
    adjacencyPairs.push_back(std::pair<int, int>(to, from));
}

int CArcGraph::VerticesCount() const
{
    return countVertices;
}

const std::vector<int> CArcGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)countVertices);
    std::vector<int> result;
    for(size_t i = 0; i < adjacencyPairs.size(); i++){
        if(vertex == adjacencyPairs[i].first){
            result.push_back(adjacencyPairs[i].second);
        }
    }
    return result;
}

const std::vector<int> CArcGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)countVertices);
    std::vector<int> result;
    for(size_t i = 0; i < adjacencyPairs.size(); i++){
        if(vertex == adjacencyPairs[i].second){
            result.push_back(adjacencyPairs[i].first);
        }
    }
    return result;
}
