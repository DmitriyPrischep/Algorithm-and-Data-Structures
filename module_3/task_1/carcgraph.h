#ifndef CARCGRAPH_H
#define CARCGRAPH_H
#include "igraph.h"

class CArcGraph : public IGraph
{
public:
    explicit CArcGraph(int verticesCount);
    ~CArcGraph() = default;

    CArcGraph(const IGraph* graph);

    void AddEdge(int from, int to);
    int VerticesCount() const;
    const std::vector<int> GetNextVertices(int vertex) const;
    const std::vector<int> GetPrevVertices(int vertex) const;
private:
    unsigned int countVertices;
    std::vector<std::pair<int, int>> adjacencyPairs;
};

#endif // CARCGRAPH_H
