#include "SimpleGraph.hpp"

int main() {
    SimpleWeightedGraph G;    // Create graph

    // Add nodes to the graph
    G.add_nodes_from({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    G.add_edges_from(
        {
            {0, 8, 2.5},
            {0, 5, 1.5},
            {1, 2, 4.0},
            {1, 3, 2.5},
            {1, 4, 3.0},
            {2, 5, 1.5},
            {2, 6, 2.0},
            {3, 6, 1.0},
            {4, 7, 2.5},
            {5, 8, 3.5},
            {6, 9, 4.0},
            {6, 4, 2.0}
        }
    );

    std::cout << "Nodi:\n";
    for (auto v : G.nodes()) {
        std::cout << v << "\n";
    }

    std::cout << "Archi e pesi:\n";
    for (auto edge : G.edges()) {
        std::cout << "Arco: (" << edge.first << ", " << edge.second << "), Peso: " << edge.third << "\n";
    }

    // std::cout << "Ordinamento topologico:\n";
    // for(auto v : G.topological_sort()) {
    //     std::cout << v << "\n";
    // }

    std::cout << "Dijkstra:\n";
    auto [pred, dist] = G.dijkstra(0);
    for (size_t i = 0; i < dist.size(); ++i) {
        std::cout << "Distanza da 0 a " << i << ": " << dist[i] 
                  << ", Predecessore: " << pred[i] << "\n";
    }

    return 0;
}