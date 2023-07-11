#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>
#include "Edge.hpp"
class Vertex{
    public:
    Vertex(std::string label, int num) : vertices(label), node(num){visitCheck = 0; distance = 0; pred = nullptr; vectorPath = {""};};
    Vertex(){};
    std::string vertices;
    //int position;
    int node;
    int visitCheck;
    int distance;
    std::vector<std::string> vectorPath;
    std::vector<Vertex *> adj;
    Vertex* pred;
};
#endif