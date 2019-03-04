#include "csetgraph.h"
#include <algorithm>
#include <assert.h>

CSetGraph::CSetGraph(int verticesCount)
{
    assert(verticesCount > 0);
    adjacencyListHash.resize(verticesCount);
}

CSetGraph::CSetGraph(IGraph *graph)
{
    for(size_t vertice = 0; vertice < (size_t)graph->VerticesCount(); vertice++){
        for(auto v : graph->GetNextVertices(vertice)){
            AddEdge(vertice, v);
        }
    }
}


void CSetGraph::AddEdge(int from, int to)
{
    assert(from >= 0 && from < (int)adjacencyListHash.size());
    assert(to >= 0 && to < (int)adjacencyListHash.size());
    adjacencyListHash[from].emplace(to);
    adjacencyListHash[to].emplace(from);
}


int CSetGraph::VerticesCount() const
{
    return adjacencyListHash.size();
}

const std::vector<int> CSetGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)adjacencyListHash.size());
    std::vector<int> vertices;
    for(auto v : adjacencyListHash[vertex]){
        vertices.push_back(v);
    }

    return vertices;
//    std::vector<int> next_vertices;
//    for (int i : array[vertex]) {
//        next_vertices.emplace_back(i);
//    }
//    return next_vertices;
}

const std::vector<int> CSetGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)adjacencyListHash.size());
    std::vector<int> vertices;
    for(size_t v = 0; v < adjacencyListHash.size(); v++){
        if(adjacencyListHash[v].find(vertex) != adjacencyListHash[v].end()){
            vertices.push_back(v);
        }
    }
    return vertices;
}
