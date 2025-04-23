#ifndef SIMPLE_WEIGHTED_UNDIRECTED_GRAPH_HPP
#define SIMPLE_WEIGHTED_UNDIRECTED_GRAPH_HPP

#include "SimpleWeightedGraphBase.hpp"

// Classe per grafi indiretti ponderati con peso double fisso
class SimpleWeightedUndirectedGraph : public SimpleWeightedGraphBase<boost::undirectedS, double> {
public:
    using Base = SimpleWeightedGraphBase<boost::undirectedS, double>;
    using Node = typename Base::Node;
};

#endif // SIMPLE_WEIGHTED_UNDIRECTED_GRAPH_HPP