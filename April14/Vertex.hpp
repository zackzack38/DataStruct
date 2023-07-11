#ifndef VECTOR_H
#define VECTOR_H
#include <string>
#include <vector>
class Vertex{
    public:
    Vertex(std::string label, int num) : vertices(label), node(num){};
    Vertex(){};
    std::string vertices;
    int position;
    int node;
    int visitCheck;
    int distance;
};
#endif