#ifndef GRAPH_H
#define GRAPH_H
#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <queue>
#include <vector>
#include <iostream>
#define N 100
class Graph : GraphBase
{
public:
    ~Graph();
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
    Vertex *findVertex(std::string label);
    Vertex *findVertex(int label);
    int allNodesVisit();

    std::deque<Vertex *> VList;
    std::deque<Edge *> EList;
    std::deque<int> adj_list[N];
    int numVertex;

private:
};
#endif