#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

int main() {

    // g++ -std=c++20 -Wall -pedantic -O3 solution.cpp -o solution
    // ./solution < example.in > solution.out
    // diff -bBZ solution.out example.expected

    typedef adjacency_list<vecS, vecS, undirectedS> Graph;
    Graph g(5); 
    add_edge(0, 1, g); 
    add_edge(1, 2, g); 
    add_edge(2, 3, g); 
    add_edge(3, 4, g); 
    add_edge(4, 0, g); 
    add_edge(0, 2, g); 
    add_edge(1, 3, g); 
    add_edge(2, 4, g);

    // Print the graph
    std::cout << "Graph edges:\n";
    for (auto it = vertices(g).first; it != vertices(g).second; ++it) {
        std::cout << *it << ": ";
        for (auto jt = out_edges(*it, g).first; jt != out_edges(*it, g).second; ++jt) {
            std::cout << target(*jt, g) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}