#include <iostream>
#include <vector>
#include "nxpp.hpp"

int main() {

    // Istanzio un grafo non diretto e non pesato
    SimpleUndirectedGraph g;
    g.add_edges_from({{0, 1}, {1, 2}, {2, 3}, {3, 0}});

    // Stampo i nodi e gli archi del grafo
    std::cout << "Nodi del grafo: ";
    for (auto node : g.nodes()) {
        std::cout << node << " " << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Archi del grafo: ";
    for (auto edge : g.edges()) {
        std::cout << "(" << edge.first << ", " << edge.second << ") " << std::endl;
    }

    return 0;
}