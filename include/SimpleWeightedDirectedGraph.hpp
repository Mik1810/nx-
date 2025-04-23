#ifndef SIMPLE_WEIGHTED_DIRECTED_GRAPH_HPP
#define SIMPLE_WEIGHTED_DIRECTED_GRAPH_HPP

#include <boost/graph/topological_sort.hpp>
#include "SimpleWeightedGraphBase.hpp"
#include <algorithm>
#include <iostream>

// Classe per grafi diretti ponderati con peso double fisso
class SimpleWeightedDirectedGraph : public SimpleWeightedGraphBase<boost::directedS, double> {
public:
    using Base = SimpleWeightedGraphBase<boost::directedS, double>;
    using Node = typename Base::Node;

    // Metodo per l'ordinamento topologico
    std::vector<Node> topological_sort() const {
        std::vector<Node> result;
        try {
            boost::topological_sort(this->g, std::back_inserter(result));
            std::reverse(result.begin(), result.end());
        } catch (const boost::not_a_dag& e) {
            std::cerr << "Errore: Il grafo contiene cicli, impossibile effettuare l'ordinamento topologico.\n";
            result.clear();
        }
        return result;
    }
};

#endif // SIMPLE_WEIGHTED_DIRECTED_GRAPH_HPP