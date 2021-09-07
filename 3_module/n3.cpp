// Copyright 2021 Alexander 'Lucifer' Orletskiy

/*
    3. «Города»
    Требуется отыскать самый выгодный маршрут между городами. 
*/

#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_set>
#include <set>
#include <functional>
#include <climits>

using std::cin;
using std::cout;
using std::endl;

/* ----------------------------- Graph Interfaces ----------------------------- */

struct IWeightGraph {
    virtual ~IWeightGraph() = default;

    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

/* ----------------------------- Weight List Graph Realization ----------------------------- */

class WeightListGraph : public IWeightGraph {
public:
    explicit WeightListGraph(size_t size) : adjacency(size) {}
    ~WeightListGraph() override = default;

    explicit WeightListGraph(const IWeightGraph & graph) : adjacency(graph.VerticesCount()) {
        for (int i = 0; i < graph.VerticesCount(); ++i)
            for (auto & j : graph.GetNextVertices(i))
                AddEdge(i, j.first, j.second);
    }

    void AddEdge(int from, int to, int weight) override {
        adjacency[from].emplace_back(std::pair<int, int>(to, weight));
    }

    int VerticesCount() const override {
        return adjacency.size();
    }

    std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override {
        return adjacency[vertex];
    }

    std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override {
        std::vector<std::pair<int, int>> prev;
        for (int i = 0; i < adjacency.size(); ++i)
            for (auto j : adjacency[i])
                if (j.first == vertex)
                    prev.emplace_back(i, j.second);
        return prev;
    }

private:
    std::vector<std::vector<std::pair<int, int>>> adjacency;
};

/* ----------------------------- Dijkstra ----------------------------- */

int find_opt_path(const IWeightGraph & graph, const int from, const int to) {
    std::vector<int> distances(graph.VerticesCount(), INT_MAX);
    std::set<std::pair<int, int>> d_set;
    distances[from] = 0;
    d_set.insert(std::make_pair(distances[from], from));

    while (!d_set.empty()) {
        int min_v = (*d_set.begin()).second;

        d_set.erase(d_set.begin());
        std::vector<std::pair<int, int>> tmp = graph.GetNextVertices(min_v);
        for (int i = 0; i < tmp.size(); i++) {
            int p_v = tmp[i].first;
            int p_d = tmp[i].second;
            if (distances[min_v] + p_d < distances[p_v]) {
                d_set.erase(std::make_pair(distances[p_v], p_v));
                distances[p_v] = distances[min_v] + p_d;
                d_set.insert(std::make_pair(distances[p_v], p_v));
            }
        }
    }
    return distances[to];
}

/* ----------------------------- main ----------------------------- */

int main() {
    size_t N, M; cin >> N >> M;

    WeightListGraph graph(N);
    for (size_t i = 0; i < M; ++i) {
        int from, to, weight; cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
        graph.AddEdge(to, from, weight);
    }

    int u, w; cin >> u >> w;

    cout << find_opt_path(graph, u, w) << endl;

    return 0;
}


/*
For tests:

6
9
0 3 1
0 4 6
1 2 7
1 3 2
1 4 3
1 5 1
2 5 3
3 4 4
3 5 6
0 4

Answer: 5
*/
