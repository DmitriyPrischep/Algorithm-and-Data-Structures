#ifndef CSETGRAPH_H
#define CSETGRAPH_H
#include <unordered_set>
#include "igraph.h"

class CSetGraph : public IGraph
{
public:
    explicit CSetGraph(int verticesCount);
    CSetGraph(IGraph* graph);
    ~CSetGraph() = default;
    void AddEdge(int from, int to);
    int VerticesCount() const;

    const std::vector<int> GetNextVertices(int vertex) const;
    const std::vector<int> GetPrevVertices(int vertex) const;
private:
    // граф хранится как массив хештаблиц.
    // индекс в массиве - номер вершины, из которой исходит ребро.
    // хештаблица хранит номера всех вершин, в которые можно попасть.
    std::vector<std::unordered_set<int>> adjacencyListHash;
};

#endif // CSETGRAPH_H
