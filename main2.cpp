#include <iostream>
#include <vector>
#include "nxpp.hpp"

int simple_undirected_graph() {
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

int simple_directed_graph() {
    // Istanzio un grafo diretto
    SimpleDirectedGraph g;
    g.add_edges_from({
        {0, 1}, 
        {1, 2}, 
        {2, 3}, 
        {1, 3}
    });

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

    // Eseguo un ordinamento topologico
    std::cout << "Nodi ordinati: ";
    for (auto node : g.topological_sort()) {
        std::cout << node << " " << std::endl;
    }

    return 0;
}

int simple_weighted_directed_graph() {
    // Istanzio un grafo diretto e pesato
    SimpleWeightedDirectedGraph g;
    g.add_edges_from({
        {0, 1, 5}, 
        {1, 2, 10}, 
        {2, 3, 15}, 
        {1, 3, 20}
    });

    // Stampo i nodi e gli archi del grafo
    std::cout << "Nodi del grafo: ";
    for (auto node : g.nodes()) {
        std::cout << node << " " << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Archi del grafo: ";
    for (auto edge : g.edges()) {
        std::cout << "(" << edge.first << ", " << edge.second << ") con peso " << edge.weight << std::endl;
    }

    // Eseguo un ordinamento topologico
    std::cout << "Nodi ordinati: ";
    for (auto node : g.topological_sort()) {
        std::cout << node << " " << std::endl;
    }

    return 0;
}

int simple_weighted_undirected_graph() {
    // Istanzio un grafo non diretto e pesato
    SimpleWeightedUndirectedGraph g;
    g.add_edges_from({{0, 1, 5}, {1, 2, 10}, {2, 3, 15}, {3, 0, 20}});

    // Stampo i nodi e gli archi del grafo
    std::cout << "Nodi del grafo: ";
    for (auto node : g.nodes()) {
        std::cout << node << " " << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Archi del grafo: ";
    for (auto edge : g.edges()) {
        std::cout << "(" << edge.first << ", " << edge.second << ") con peso " << edge.weight << std::endl;
    }

    return 0;
}

int main() {

    // Esempio di utilizzo della classe SimpleUndirectedGraph
    std::cout << "Esempio di grafo non diretto e non pesato:" << std::endl;
    simple_undirected_graph();

    // Esempio di utilizzo della classe SimpleDirectedGraph
    std::cout << "Esempio di grafo diretto:" << std::endl;
    simple_directed_graph();

    // Esempio di utilizzo della classe SimpleWeightedDirectedGraph
    std::cout << "Esempio di grafo diretto e pesato:" << std::endl;
    simple_weighted_directed_graph();

    // Esempio di utilizzo della classe SimpleWeightedUndirectedGraph
    std::cout << "Esempio di grafo non diretto e pesato:" << std::endl;
    simple_weighted_undirected_graph();

    return 0;
}