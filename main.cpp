#include "SimpleGraph.h"


int main() {


    SimpleGraph G;    // Create graph

    // Add nodes to the graph
    //G.add_nodes(10);

    G.add_nodes_from({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    G.add_edges_from(
        {
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 5},
            {2, 6},
            {3, 6},
            {4, 7},
            {5, 8},
            {6, 9},
            {6, 4}
        }
    );

    // auto a = G.add_node();
    // auto b = G.add_node();
    // auto c = G.add_node();
    // auto d = G.add_node();
    // auto e = G.add_node();
    // auto f = G.add_node();
    // auto g = G.add_node();
    // auto h = G.add_node();

    // Make a map that maps each integer to respective alphabet letter
    // std::map<int, char> intToAlphabet;
    // char letter = 'a';
    // for (int i = 0; i < 26; ++i) {
    //     intToAlphabet[i] = letter++;
    // }


    // G.add_edge(a, b);
    // G.add_edge(a, c);
    // G.add_edge(c, d);
    // G.add_edge(c, e);
    // G.add_edge(b, f);
    // G.add_edge(f, g);
    // G.add_edge(g, h);

    //G.set_node_attr(a, "label", "A");
    //G.set_node_attr(b, "label", "B");

    std::cout << "Nodi:\n";
    for (SimpleGraph::Node v : G.nodes()) {
        std::cout << v  << "\n";
    }

    std::cout << "Archi:\n";
    for (auto [u, v] : G.edges()) {
        std::cout << "(" << u << ", " << v << ")\n";
    }

    return 0;
}
