// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    1. «Представление графа»
    Дан базовый интерфейс для представления ориентированного графа:
    struct IGraph {
        virtual ~IGraph() {}
            
        // Добавление ребра от from к to.
        virtual void AddEdge(int from, int to) = 0;

        virtual int VerticesCount() const  = 0;

        virtual std::vector<int> GetNextVertices(int vertex) const = 0;
        virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
    };

    Необходимо написать несколько реализаций интерфейса:
     - ListGraph, хранящий граф в виде массива списков смежности,
     - MatrixGraph, хранящий граф в виде матрицы смежности,
     - SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
     - ArcGraph, хранящий граф в виде одного массива пар {from, to}.
    Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
    Число вершин графа задается в конструкторе каждой реализации. 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_set>
#include <functional>

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

/* ----------------------------- Graph Realization ----------------------------- */

// List Graph

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

// Matrix Graph

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(size_t size) : adjacency(size, std::vector<int>(size, 0)) {}
    ~MatrixGraph() override = default;

    explicit MatrixGraph(const IGraph & graph) : adjacency(graph.VerticesCount(), std::vector<int>(graph.VerticesCount(), 0)) {
        for (int i = 0; i < graph.VerticesCount(); ++i)
            for (auto & j : graph.GetNextVertices(i))
                AddEdge(i, j);
    }

    void AddEdge(int from, int to) override {
        adjacency[from][to] = 1;
    }

    int VerticesCount() const override {
        return adjacency.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> next;
        for (int i = 0; i < adjacency.size(); ++i)
            if (adjacency[vertex][i] != 0)
                next.emplace_back(i);
        return next;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> prev;
        for (int i = 0; i < adjacency.size(); ++i)
            if (adjacency[i][vertex] == 1)
                prev.emplace_back(i);
        return prev;
    }

private:
    std::vector<std::vector<int>> adjacency;
};

// Set Graph

class SetGraph : public IGraph {
public:
    explicit SetGraph(size_t size) : adjacency(size) {}
    ~SetGraph() override = default;

    explicit SetGraph(const IGraph & graph) : adjacency(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i)
            for (auto & j : graph.GetNextVertices(i))
                AddEdge(i, j);
    }

    void AddEdge(int from, int to) override {
        adjacency[from].insert(to);
    }

    int VerticesCount() const override {
        return adjacency.size();
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> next;
        for (auto & vertex_i : adjacency[vertex])
            next.emplace_back(vertex_i);
        return next;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> prev;
        for (int i = 0; i < adjacency.size(); ++i)
            if (adjacency[i].find(vertex) != adjacency[i].end())
                prev.emplace_back(i);
        return prev;
    }

private:
    std::vector<std::unordered_set<int>> adjacency;
};

// Arc Graph

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(size_t size) : size(size) {}
    ~ArcGraph() override = default;

    explicit ArcGraph(const IGraph & graph) : size(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i)
            for (auto & j : graph.GetNextVertices(i))
                AddEdge(i, j);
    }

    void AddEdge(int from, int to) override {
        adjacency.emplace_back(from, to);
    }

    int VerticesCount() const override {
        return size;
    }

    std::vector<int> GetNextVertices(int vertex) const override {
        std::vector<int> next;
        for (auto & vertex_i : adjacency)
            if (vertex_i.first == vertex)
                next.emplace_back(vertex_i.second);
        return next;
    }

    std::vector<int> GetPrevVertices(int vertex) const override {
        std::vector<int> prev;
        for (auto & vertex_i : adjacency)
            if (vertex_i.second == vertex)
                prev.emplace_back(vertex_i.first);
        return prev;
    }

private:
    size_t size;
    std::vector<std::pair<int, int>> adjacency;
};

/* ----------------------------- functions ----------------------------- */

// DFS

void DFS(const IGraph & graph, int vertex, std::vector<bool> & visited, std::function<void(int)> & callback) {
    visited[vertex] = true;
    callback(vertex);
    for (int next : graph.GetNextVertices(vertex))
        if (!visited[next])
            DFS(graph, next, visited, callback);
}

void mainDFS(const IGraph & graph, std::function<void(int)> callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i)
        if (!visited[i])
            DFS(graph, i, visited, callback);
}

// Topological Sort

void topologicalSort(const IGraph & graph, int vertex, std::vector<bool> & visited, std::deque<int> & sorted) {
    visited[vertex] = true;
    for (int nextVertex : graph.GetNextVertices(vertex))
        if (!visited[nextVertex])
            topologicalSort(graph, nextVertex, visited, sorted);
    sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph & graph) {
    std::deque<int> sorted;
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i)
        if (!visited[i])
            topologicalSort(graph, i, visited, sorted);
    return sorted;
}

// BFS

void BFS(const IGraph & graph, int vertex, std::vector<bool> & visited, const std::function<void(int)> & callback) {
    std::queue<int> queue;
    queue.push(vertex);
    visited[vertex] = true;
    while (!queue.empty()) {
        int current_vertex = queue.front();
        queue.pop();
        callback(current_vertex);
        for (int next : graph.GetNextVertices(current_vertex))
            if (!visited[next]) {
                visited[next] = true;
                queue.push(next);
            }
    }
}

void mainBFS(const IGraph & graph, const std::function<void(int)> & callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (int i = 0; i < graph.VerticesCount(); ++i)
        if (!visited[i])
            BFS(graph, i, visited, callback);
}

/* ----------------------------- main ----------------------------- */

int main() {
    ListGraph lgraph(7);
    lgraph.AddEdge(0, 1); lgraph.AddEdge(0, 5);
    lgraph.AddEdge(1, 2); lgraph.AddEdge(1, 3); lgraph.AddEdge(1, 5); lgraph.AddEdge(1, 6);
    lgraph.AddEdge(3, 2); lgraph.AddEdge(3, 4); lgraph.AddEdge(3, 6);
    lgraph.AddEdge(5, 4); lgraph.AddEdge(5, 6);
    lgraph.AddEdge(6, 4);

    MatrixGraph mgraph(lgraph);
    SetGraph sgraph(mgraph);
    ArcGraph agraph(sgraph);

    cout << "ListGraph:" << endl;
    mainBFS(lgraph, [](int vertex) { cout << vertex << " "; });
    cout << endl << "Vertices: " << lgraph.VerticesCount() << endl << endl;

    cout << "MatrixGraph:" << endl;
    mainBFS(mgraph, [](int vertex) { cout << vertex << " "; });
    cout << endl << "Vertices: " << mgraph.VerticesCount() << endl << endl;

    cout << "SetGraph:" << endl;
    mainBFS(sgraph, [](int vertex) { cout << vertex << " "; });
    cout << endl << "Vertices: " << sgraph.VerticesCount() << endl << endl;

    cout << "ArcGraph:" <<  endl;
    mainBFS(agraph, [](int vertex) { cout << vertex << " "; });
    cout << endl << "Vertices: " << agraph.VerticesCount() << endl << endl;

    return 0;
}
