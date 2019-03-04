#include <iostream>
#include <assert.h>
#include <vector>
#include <set>

using namespace std;

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(size_t from, size_t to, size_t weight) = 0;
    virtual size_t VerticesCount() const  = 0;
    virtual const std::vector<std::pair<size_t, size_t>> GetNextVertices(size_t vertex) const = 0;
    virtual const std::vector<std::pair<size_t, size_t>> GetPrevVertices(size_t vertex) const = 0;
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

    void AddEdge(size_t from, size_t to, size_t weight);
    size_t VerticesCount() const;
    const std::vector<std::pair<size_t, size_t>> GetNextVertices(size_t vertex) const;
    const std::vector<std::pair<size_t, size_t>> GetPrevVertices(size_t vertex) const;
private:
    std::vector<std::vector<std::pair<size_t, size_t>>> adjacencyLists;
};

CListGraph::CListGraph(int verticesCount)
{
    assert(verticesCount > 0);
    adjacencyLists.resize(verticesCount);
}

CListGraph::CListGraph(IGraph *graph)
{
    assert(graph);
    adjacencyLists.resize(graph->VerticesCount());
    for(size_t vertice = 0; vertice < (size_t)graph->VerticesCount(); vertice++){
        std::vector<std::pair<size_t, size_t>> next_vertices = graph->GetNextVertices(vertice);
        for(auto v : next_vertices){
            AddEdge(vertice, v.first, v.second);
        }
    }
}

void CListGraph::AddEdge(size_t from, size_t to, size_t weight)
{
    assert(from < adjacencyLists.size());
    assert(to < adjacencyLists.size());
    adjacencyLists[from].emplace_back(std::make_pair(to, weight));
    adjacencyLists[to].emplace_back(std::make_pair(from, weight));
}

size_t CListGraph::VerticesCount() const
{
    return adjacencyLists.size();
}
const std::vector<std::pair<size_t, size_t>> CListGraph::GetNextVertices(size_t vertex) const
{
    assert(vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

const std::vector<std::pair<size_t, size_t>> CListGraph::GetPrevVertices(size_t vertex) const
{
    assert(vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

size_t ShortRoad(IGraph* graph, size_t start, size_t finish)
{
    assert(graph);
    assert(start < graph->VerticesCount());
    assert(finish < graph->VerticesCount());
    std::vector<int> visited(graph->VerticesCount(), -1);
    std::set<std::pair<size_t, size_t>> priorityQueue;
    priorityQueue.insert(std::make_pair(start, 0));
    visited[start] = 0;

    while(!priorityQueue.empty()){
        size_t from = priorityQueue.begin()->first;
        priorityQueue.erase(priorityQueue.begin());
        std::vector<std::pair<size_t, size_t>> nextVertices = graph->GetNextVertices(from);
        for(auto to : nextVertices){
            if(visited[to.first] > (visited[from] + to.second)){
                if(visited[to.first] != -1){
                    priorityQueue.erase(std::make_pair(visited[to.first], to.first));
                }
                visited[to.first] = visited[from] + to.second;
                priorityQueue.insert(to);
            }
        }
    }
    return visited[finish];
}

int main()
{
    size_t count_towns = 0;
    std::cin >> count_towns;
    size_t count_roads = 0;
    std::cin >> count_roads;

    IGraph* graph = new CListGraph(count_towns);
    for (size_t i = 0; i < count_roads; i++){
        size_t from = 0;
        size_t to = 0;
        size_t weight = 0;
        std::cin >> from >> to >> weight;
        graph->AddEdge(from, to, weight);
    }
    size_t start_pos = 0;
    size_t finish_pos = 0;
    std::cin >> start_pos >> finish_pos;
    cout << ShortRoad(graph, start_pos, finish_pos) << endl;
    delete graph;
    return 0;
}
