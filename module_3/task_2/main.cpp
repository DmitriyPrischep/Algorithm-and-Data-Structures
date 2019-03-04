#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual const std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual const std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class CListGraph : public IGraph
{
public:
    explicit CListGraph(int verticesCount);
    CListGraph(IGraph* graph);
    CListGraph(const CListGraph& graph) = delete;
    CListGraph(const CListGraph&& graph) = delete;
    CListGraph& operator =(const CListGraph& graph) = delete;
    CListGraph& operator =(const CListGraph&& graph) = delete;
    ~CListGraph() = default;

    void AddEdge(int from, int to);
    int VerticesCount() const;
    const std::vector<int> GetNextVertices(int vertex) const;
    const std::vector<int> GetPrevVertices(int vertex) const;
private:
    std::vector<std::vector<int>> adjacencyLists;
};

CListGraph::CListGraph(int verticesCount)
{
    assert(verticesCount > 0);
    adjacencyLists.resize(verticesCount);
}

CListGraph::CListGraph(IGraph *graph)
{
    adjacencyLists.resize(graph->VerticesCount());
    for(size_t vertice = 0; vertice < (size_t)graph->VerticesCount(); vertice++){
        std::vector<int> next_vertices = graph->GetNextVertices(vertice);
        for(auto v : next_vertices){
            AddEdge(vertice, v);
        }
    }
}

void CListGraph::AddEdge(int from, int to)
{
    assert(from >= 0 && from < (int)adjacencyLists.size());
    assert(to >= 0 && to < (int)adjacencyLists.size());
    adjacencyLists[from].push_back(to);
    adjacencyLists[to].push_back(from);
}

int CListGraph::VerticesCount() const
{
    return adjacencyLists.size();
}
const std::vector<int> CListGraph::GetNextVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)adjacencyLists.size());
    return adjacencyLists[vertex];
}

const std::vector<int> CListGraph::GetPrevVertices(int vertex) const
{
    assert(vertex >= 0 && vertex < (int)adjacencyLists.size());
    return adjacencyLists[vertex];
}

size_t MinPath(IGraph *graph, size_t start, size_t finish)
{
    assert(start < (size_t)graph->VerticesCount());
    assert(finish < (size_t)graph->VerticesCount());
    std::queue<size_t> grey_vertices;
    std::vector<size_t> count_min_path(graph->VerticesCount());
    std::vector<size_t> depth_vertices(graph->VerticesCount());
    grey_vertices.emplace(start);
    count_min_path[start] = 1;

    while (!grey_vertices.empty()){
        size_t temp = grey_vertices.front();
        grey_vertices.pop();
        std::vector<int> adjacent_vertices = graph->GetNextVertices(temp);

        for(size_t vertex : adjacent_vertices){
            if(!count_min_path[vertex]){
                grey_vertices.emplace(vertex);
                depth_vertices[vertex] = depth_vertices[temp] + 1;
                count_min_path[vertex] = count_min_path[temp];
            } else if(depth_vertices[vertex] == depth_vertices[temp] + 1){
                count_min_path[vertex] += count_min_path[temp];
            }
        }
    }
    return count_min_path[finish];
}

int main()
{
    size_t count_vertices = 0;
    std::cin >> count_vertices;
    size_t count_edges = 0;
    std::cin >> count_edges;

    CListGraph *graph = new CListGraph(count_vertices);
    for(size_t i = 0; i < count_edges; i++){
        size_t begin_edge = 0;
        size_t end_edge = 0;
        std::cin >> begin_edge >> end_edge;
        graph->AddEdge(begin_edge, end_edge);
    }

    size_t start_pos = 0;
    size_t finish_pos = 0;
    std::cin >> start_pos >> finish_pos;

    std::cout << MinPath(graph, start_pos, finish_pos) << std::endl;
    return 0;
}
