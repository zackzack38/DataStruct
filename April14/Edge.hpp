#ifndef EDGE_H
#define EDGE_H
#include <string>
#include <cstddef>
#include "Vertex.hpp"

class Edge{
    public:
    Edge(std::string first, std::string second, unsigned long weight) : as(first), bs(second), w(weight){};
    Edge(Vertex* first, Vertex* second, unsigned long weight) : a(first), b(second), w(weight){};
    Vertex* a;
    Vertex* b;
    std::string as;
    std::string bs;
    unsigned long w;
};
#endif