#ifndef CMATRIXGRAPH_H
#define CMATRIXGRAPH_H
#include "igraph.h"

class CMatrixGraph : public IGraph
{
public:
     explicit CMatrixGraph(int verticesCount);
     CMatrixGraph(const IGraph* graph);
    ~CMatrixGraph() = default;

    void AddEdge(int from, int to);
    int VerticesCount() const;
    const std::vector<int> GetNextVertices(int vertex) const;
    const std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::vector<bool>> adjacencyMatrix;
};

#endif // CMATRIXGRAPH_H
