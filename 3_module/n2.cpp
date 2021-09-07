// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    2. Количество различных путей
    Дан невзвешенный неориентированный граф.
    В графе может быть несколько кратчайших путей между какими-то вершинами.
    Найдите количество различных кратчайших путей между заданными вершинами. 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_set>
#include <functional>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

/* ----------------------------- Graph Interface ----------------------------- */

struct IGraph {
    virtual ~IGraph() {}
    
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

/* ----------------------------- List Graph Realization ----------------------------- */

class ListGraph : public IGraph {
public:
    explicit ListGraph(size_t size) : adjacency(size) {}
    ~ListGraph() override = default;

    explicit ListGraph(const IGraph & graph) : adjacency(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i)
            for (auto & j : graph.GetNextVertices(i))
                AddEdge(i, j);
    }

    void AddEdge(int from, int to) override {
        adjacency[from].emplace_back(to);
    }

    int VerticesCount() const override {
        return adjacency.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        return adjacency[vertex];
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> prev;
        for (int i = 0; i < adjacency.size(); ++i)
            for (int j : adjacency[i])
                if (j == vertex)
                    prev.emplace_back(i);
        return prev;
    }

private:
    std::vector<std::vector<int>> adjacency;
};

/* ----------------------------- BFS ----------------------------- */


void BFS(const IGraph & graph, const int start, std::vector<bool> & visited, const std::function<void(int, int)> & callback) {
    std::queue<int> queue;
    queue.push(start);

    while (!queue.empty()) {
        int current_vertex = queue.front();
        queue.pop();
        if (!visited[current_vertex]) {
            visited[current_vertex] = true;
            for (const int & next : graph.GetNextVertices(current_vertex)) {
                queue.push(next);
                callback(current_vertex, next);
            }
        }
    }
}

void mainBFS(const IGraph & graph, const int start, const std::function<void(int, int)> & callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    BFS(graph, start, visited, callback);
    for (size_t i = 0; i < graph.VerticesCount(); ++i)
        if (!visited[i])
            BFS(graph, i, visited, callback);
}

/* ----------------------------- Count shortest paths ----------------------------- */

size_t shortest_paths_count(const IGraph & graph, const int from, const int to) {
    std::vector<std::pair<int, int>> nodes(graph.VerticesCount(), {INT_MAX, 0});

    nodes[from] = {0, 1};

    mainBFS(graph, from, [&](int vertex, int next) {
        if (nodes[vertex].first == nodes[next].first - 1) {
            nodes[next].second += nodes[vertex].second;
        }
        if (nodes[vertex].first < nodes[next].first - 1) {
            nodes[next] = { nodes[vertex].first + 1, nodes[vertex].second };
        }
    });

    return nodes[to].second;
}

/* ----------------------------- main ----------------------------- */

int main() {
    size_t v, n; cin >> v >> n;

    ListGraph graph(v);

    for (size_t i = 0; i < n; ++i) {
        size_t from, to;
        cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    size_t u, w; cin >> u >> w;

    cout << shortest_paths_count(graph, u, w) << endl;

    return 0;
}
