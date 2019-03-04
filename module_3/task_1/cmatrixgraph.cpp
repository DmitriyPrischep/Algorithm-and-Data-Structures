#include "cmatrixgraph.h"
#include <assert.h>

CMatrixGraph::CMatrixGraph(int verticesCount)
{
    assert(verticesCount > 0);
    adjacencyMatrix.resize(verticesCount, std::vector<bool>(verticesCount));
}

CMatrixGraph::CMatrixGraph(const IGraph* graph)
{
    assert(graph != nullptr);
    assert(graph->VerticesCount() > 0);
    adjacencyMatrix.resize(graph->VerticesCount(), std::vector<bool>(graph->VerticesCount()));
    for(size_t vertice = 0; vertice < (size_t)graph->VerticesCount(); vertice++){
        for(auto v : graph->GetNextVertices(vertice)){
            AddEdge(vertice, v);
        }
    }
}

void CMatrixGraph::AddEdge(int from, int to)
{
    assert(from >= 0 && from < (int)adjacencyMatrix.size());
    assert(to >= 0 && to < (int)adjacencyMatrix.size());
    adjacencyMatrix[from][to] = true;
}
int CMatrixGraph::VerticesCount() const
{
    return adjacencyMatrix.size();
}
const std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)adjacencyMatrix.size());
    std::vector<int> result;
    for(size_t i = 0; i < adjacencyMatrix[vertex].size(); i++){
        if(adjacencyMatrix[vertex][i])
            result.push_back(i);
    }
    return result;
}
const std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)adjacencyMatrix.size());
    std::vector<int> result;
    for(size_t i = 0; i < adjacencyMatrix.size(); i++){
        if(adjacencyMatrix[i][vertex])
            result.push_back(i);
    }
    return result;
}
