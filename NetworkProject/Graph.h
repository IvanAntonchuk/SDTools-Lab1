#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

/**
 * @brief Інтерфейс для роботи з графами мережі.
 *
 * Визначає базові операції, які має підтримувати будь-яка реалізація графа
 * (додавання/видалення вершин та ребер).
 */
class Graph {
public:
    /**
     * @brief Додає нову вершину (вузол) у граф.
     * @param node Номер вершини.
     */
    virtual void addNode(int node) = 0;

    /**
     * @brief Додає ребро між двома вершинами.
     * @param from Початкова вершина.
     * @param to Кінцева вершина.
     */
    virtual void addEdge(int from, int to) = 0;

    /**
     * @brief Видаляє вершину та всі пов'язані з нею ребра.
     * @param node Номер вершини.
     */
    virtual void removeNode(int node) = 0;

    /**
     * @brief Видаляє ребро між вершинами.
     * @param from Початкова вершина.
     * @param to Кінцева вершина.
     */
    virtual void removeEdge(int from, int to) = 0;

    /**
     * @brief Перевіряє наявність ребра.
     * @param from Початкова вершина.
     * @param to Кінцева вершина.
     * @return true, якщо ребро існує.
     */
    virtual bool hasEdge(int from, int to) const = 0;

    /**
     * @brief Виводить структуру графа у консоль.
     */
    virtual void displayGraph() const = 0;

    virtual ~Graph() {}
};

/**
 * @brief Реалізація графа на основі списку суміжності.
 * Ефективна для розріджених графів.
 */
class AdjacencyListGraph : public Graph {
private:
    std::vector<std::vector<int>> adjList; ///< Список суміжності
public:
    void addNode(int node) override;
    void addEdge(int from, int to) override;
    void removeNode(int node) override;
    void removeEdge(int from, int to) override;
    bool hasEdge(int from, int to) const override;
    void displayGraph() const override;
};

/**
 * @brief Реалізація графа на основі матриці суміжності.
 * Ефективна для щільних графів.
 */
class AdjacencyMatrixGraph : public Graph {
private:
    std::vector<std::vector<int>> matrix; ///< Матриця суміжності (0/1)
public:
    void addNode(int node) override;
    void addEdge(int from, int to) override;
    void removeNode(int node) override;
    void removeEdge(int from, int to) override;
    bool hasEdge(int from, int to) const override;
    void displayGraph() const override;
};

/**
 * @brief Орієнтований граф (Directed Graph).
 * Ребра мають напрямок (from -> to).
 */
class DirectedGraph : public Graph {
private:
    std::vector<std::pair<int, int>> edges; ///< Список ребер
public:
    void addNode(int node) override;
    void addEdge(int from, int to) override;
    void removeNode(int node) override;
    void removeEdge(int from, int to) override;
    bool hasEdge(int from, int to) const override;
    void displayGraph() const override;
};
#endif