#include <assert.h>
#include "clistgraph.h"

CListGraph::CListGraph(int verticesCount)
{
    assert(verticesCount > 0);
    inAdjacencyLists.resize(verticesCount);
    outAdjacencyLists.resize(verticesCount);
}

CListGraph::CListGraph(IGraph *graph)
{
    assert(graph != nullptr);
    assert(graph->VerticesCount() > 0);
    inAdjacencyLists.resize(graph->VerticesCount());
    outAdjacencyLists.resize(graph->VerticesCount());

    for(size_t vertice = 0; vertice < (size_t)graph->VerticesCount(); vertice++){
        std::vector<int> next_vertices = graph->GetNextVertices(vertice);
        for(auto v : next_vertices){
            AddEdge(vertice, v);
        }
    }
}

void CListGraph::AddEdge(int from, int to)
{
    assert(from >= 0 && from < (int)inAdjacencyLists.size());
    assert(to >= 0 && to < (int)inAdjacencyLists.size());
    outAdjacencyLists[from].push_back(to);
    inAdjacencyLists[to].push_back(from);
}

int CListGraph::VerticesCount() const
{
    return inAdjacencyLists.size();
}
const std::vector<int> CListGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)outAdjacencyLists.size());
    return outAdjacencyLists[vertex];
}

const std::vector<int> CListGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)inAdjacencyLists.size());
    return inAdjacencyLists[vertex];
}

