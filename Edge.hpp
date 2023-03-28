#ifndef Edge
#define Edge

#include <iostream>
class Edge {
public:
    int src, dest, weight;

    Edge(int src, int dest, int weight)
        : src(src), dest(dest), weight(weight) {}
};

#endif
