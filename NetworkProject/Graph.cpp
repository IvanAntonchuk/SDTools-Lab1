#include "Graph.h"

void AdjacencyListGraph::addNode(int node) { adjList.resize(node + 1); }
void AdjacencyListGraph::addEdge(int from, int to) { adjList[from].push_back(to); }
void AdjacencyListGraph::removeNode(int node) { adjList[node].clear(); }
void AdjacencyListGraph::removeEdge(int from, int to) {
    auto& vec = adjList[from];
    vec.erase(std::remove(vec.begin(), vec.end(), to), vec.end());
}
void AdjacencyListGraph::displayGraph() const {
    for (size_t i = 0; i < adjList.size(); i++) {
        std::cout << i << ": ";
        for (int j : adjList[i]) std::cout << j << " ";
        std::cout << "\n";
    }
}

void AdjacencyMatrixGraph::addNode(int node) { matrix.resize(node + 1, std::vector<int>(node + 1, 0)); }
void AdjacencyMatrixGraph::addEdge(int from, int to) { matrix[from][to] = 1; }
void AdjacencyMatrixGraph::removeNode(int node) {
    for (auto& row : matrix) row[node] = 0;
}
void AdjacencyMatrixGraph::removeEdge(int from, int to) { matrix[from][to] = 0; }
void AdjacencyMatrixGraph::displayGraph() const {
    for (auto& row : matrix) {
        for (int val : row) std::cout << val << " ";
        std::cout << "\n";
    }
}

void DirectedGraph::addNode(int node) {}
void DirectedGraph::addEdge(int from, int to) { edges.push_back({ from,to }); }
void DirectedGraph::removeNode(int node) {
    edges.erase(std::remove_if(edges.begin(), edges.end(), [node](auto& e) {return e.first == node || e.second == node; }), edges.end());
}
void DirectedGraph::removeEdge(int from, int to) {
    edges.erase(std::remove(edges.begin(), edges.end(), std::make_pair(from, to)), edges.end());
}
void DirectedGraph::displayGraph() const {
    for (auto& e : edges) std::cout << e.first << "->" << e.second << "\n";
}

bool AdjacencyListGraph::hasEdge(int from, int to) const {
    if (from >= adjList.size()) return false;
    for (int node : adjList[from]) {
        if (node == to) return true;
    }
    return false;
}

bool AdjacencyMatrixGraph::hasEdge(int from, int to) const {
    if (from >= matrix.size() || to >= matrix[from].size()) return false;
    return matrix[from][to] == 1;
}

bool DirectedGraph::hasEdge(int from, int to) const {
    for (const auto& edge : edges) {
        if (edge.first == from && edge.second == to) return true;
    }
    return false;
}