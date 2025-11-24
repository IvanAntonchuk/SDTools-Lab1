#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

class Graph {
public:
    virtual void addNode(int node) = 0;
    virtual void addEdge(int from, int to) = 0;
    virtual void removeNode(int node) = 0;
    virtual void removeEdge(int from, int to) = 0;
    virtual void displayGraph() const = 0;
    virtual ~Graph() {}
};

class AdjacencyListGraph : public Graph {
private:
    std::vector<std::vector<int>> adjList;
public:
    void addNode(int node) override;
    void addEdge(int from, int to) override;
    void removeNode(int node) override;
    void removeEdge(int from, int to) override;
    void displayGraph() const override;
};

class AdjacencyMatrixGraph : public Graph {
private:
    std::vector<std::vector<int>> matrix;
public:
    void addNode(int node) override;
    void addEdge(int from, int to) override;
    void removeNode(int node) override;
    void removeEdge(int from, int to) override;
    void displayGraph() const override;
};

class DirectedGraph : public Graph {
private:
    std::vector<std::pair<int, int>> edges;
public:
    void addNode(int node) override;
    void addEdge(int from, int to) override;
    void removeNode(int node) override;
    void removeEdge(int from, int to) override;
    void displayGraph() const override;
};
#endif