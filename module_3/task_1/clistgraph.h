#ifndef CLISTGRAPH_H
#define CLISTGRAPH_H
#include <vector>
#include "igraph.h"

class CListGraph : public IGraph
{
public:
    explicit CListGraph(int verticesCount);
    CListGraph(IGraph* graph);
//    CListGraph(const CListGraph& graph) = delete;
//    CListGraph(const CListGraph&& graph) = delete;
//    CListGraph& operator =(const CListGraph& graph) = delete;
//    CListGraph& operator =(const CListGraph&& graph) = delete;
    ~CListGraph() = default;

    void AddEdge(int from, int to);
    int VerticesCount() const;

    virtual const std::vector<int> GetNextVertices(int vertex) const;
    virtual const std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::vector<int>> inAdjacencyLists;
    std::vector<std::vector<int>> outAdjacencyLists;
};

#endif // CLISTGRAPH_H
