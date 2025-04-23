#ifndef NXPP_HPP
#define NXPP_HPP

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/topological_sort.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>

// Struttura Triple per rappresentare un arco pesato
template <typename T1, typename T2, typename T3>
struct EdgeTriple {
    T1 first;
    T2 second;
    T3 weight;
    
    EdgeTriple(T1 f, T2 s, T3 w) : first(f), second(s), weight(w) {}
};

// Classe base per grafi semplici
class SimpleGraph {
public:
    using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
    using Node = boost::graph_traits<GraphType>::vertex_descriptor;
    using Edge = boost::graph_traits<GraphType>::edge_descriptor;

    SimpleGraph() : g() {}
    virtual ~SimpleGraph() {}

    virtual Node add_node() {
        return boost::add_vertex(g);
    }

    virtual void add_nodes_from(const std::vector<Node>& nodes) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            add_node();
        }
    }

    virtual Edge add_edge(Node u, Node v) {
        return boost::add_edge(u, v, g).first;
    }

    virtual void add_edges_from(const std::vector<std::pair<Node, Node>>& edges) {
        for (const auto& edge : edges) {
            add_edge(edge.first, edge.second);
        }
    }

    virtual std::vector<Node> nodes() const {
        std::vector<Node> result;
        for (auto [v, vend] = boost::vertices(g); v != vend; ++v) {
            result.push_back(*v);
        }
        return result;
    }

    virtual std::vector<std::pair<Node, Node>> edges() const {
        std::vector<std::pair<Node, Node>> result;
        for (auto [e, eend] = boost::edges(g); e != eend; ++e) {
            result.emplace_back(boost::source(*e, g), boost::target(*e, g));
        }
        return result;
    }

protected:
    GraphType g;
};

// Classe per grafi diretti
class SimpleDirectedGraph {
public:
    using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS>;
    using Node = boost::graph_traits<GraphType>::vertex_descriptor;
    using Edge = boost::graph_traits<GraphType>::edge_descriptor;

    SimpleDirectedGraph() : g() {}
    virtual ~SimpleDirectedGraph() {}

    Node add_node() {
        return boost::add_vertex(g);
    }

    void add_nodes_from(const std::vector<Node>& nodes) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            add_node();
        }
    }

    Edge add_edge(Node u, Node v) {
        return boost::add_edge(u, v, g).first;
    }

    void add_edges_from(const std::vector<std::pair<Node, Node>>& edges) {
        for (const auto& edge : edges) {
            add_edge(edge.first, edge.second);
        }
    }

    std::vector<Node> nodes() const {
        std::vector<Node> result;
        for (auto [v, vend] = boost::vertices(g); v != vend; ++v) {
            result.push_back(*v);
        }
        return result;
    }

    std::vector<std::pair<Node, Node>> edges() const {
        std::vector<std::pair<Node, Node>> result;
        for (auto [e, eend] = boost::edges(g); e != eend; ++e) {
            result.emplace_back(boost::source(*e, g), boost::target(*e, g));
        }
        return result;
    }

    // Metodo per l'ordinamento topologico
    std::vector<Node> topological_sort() const {
        std::vector<Node> result;
        try {
            // Utilizzo della funzione topological_sort di Boost
            boost::topological_sort(g, std::back_inserter(result));
            // Invertiamo l'ordine poiché boost::topological_sort 
            // inserisce i nodi in ordine inverso
            std::reverse(result.begin(), result.end());
        } catch (boost::not_a_dag& e) {
            std::cerr << "Error: Il grafo contiene cicli, impossibile effettuare l'ordinamento topologico.\n";
            // Svuotiamo il risultato in caso di errore
            result.clear();
        }
        return result;
    }

protected:
    GraphType g;
};

// Classe per grafi indiretti
class SimpleUndirectedGraph {
public:
    using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
    using Node = boost::graph_traits<GraphType>::vertex_descriptor;
    using Edge = boost::graph_traits<GraphType>::edge_descriptor;

    SimpleUndirectedGraph() : g() {}
    virtual ~SimpleUndirectedGraph() {}

    Node add_node() {
        return boost::add_vertex(g);
    }

    void add_nodes_from(const std::vector<Node>& nodes) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            add_node();
        }
    }

    Edge add_edge(Node u, Node v) {
        return boost::add_edge(u, v, g).first;
    }

    void add_edges_from(const std::vector<std::pair<Node, Node>>& edges) {
        for (const auto& edge : edges) {
            add_edge(edge.first, edge.second);
        }
    }

    std::vector<Node> nodes() const {
        std::vector<Node> result;
        for (auto [v, vend] = boost::vertices(g); v != vend; ++v) {
            result.push_back(*v);
        }
        return result;
    }

    std::vector<std::pair<Node, Node>> edges() const {
        std::vector<std::pair<Node, Node>> result;
        for (auto [e, eend] = boost::edges(g); e != eend; ++e) {
            result.emplace_back(boost::source(*e, g), boost::target(*e, g));
        }
        return result;
    }

protected:
    GraphType g;
};

// Template per grafi ponderati
template <typename DirectedS>
class SimpleWeightedGraphBase {
public:
    using WeightType = double;
    using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, DirectedS,
                                            boost::no_property, boost::property<boost::edge_weight_t, WeightType>>;
    using Node = typename boost::graph_traits<GraphType>::vertex_descriptor;
    using Edge = typename boost::graph_traits<GraphType>::edge_descriptor;
    using WeightMap = typename boost::property_map<GraphType, boost::edge_weight_t>::type;
    using WeightedEdge = EdgeTriple<Node, Node, WeightType>;

    SimpleWeightedGraphBase() : g(), weight_map(boost::get(boost::edge_weight, g)) {}
    virtual ~SimpleWeightedGraphBase() {}

    Node add_node() {
        return boost::add_vertex(g);
    }

    void add_nodes_from(const std::vector<Node>& nodes) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            add_node();
        }
    }

    Edge add_edge(Node u, Node v, WeightType weight) {
        Edge e = boost::add_edge(u, v, g).first;
        weight_map[e] = weight;
        return e;
    }

    void add_edges_from(const std::vector<std::tuple<Node, Node, WeightType>>& edges) {
        for (const auto& edge : edges) {
            add_edge(std::get<0>(edge), std::get<1>(edge), std::get<2>(edge));
        }
    }

    std::vector<Node> nodes() const {
        std::vector<Node> result;
        for (auto [v, vend] = boost::vertices(g); v != vend; ++v) {
            result.push_back(*v);
        }
        return result;
    }

    std::vector<WeightedEdge> edges() const {
        std::vector<WeightedEdge> result;
        for (auto [e, eend] = boost::edges(g); e != eend; ++e) {
            result.emplace_back(boost::source(*e, g), boost::target(*e, g), weight_map[*e]);
        }
        return result;
    }

protected:
    GraphType g;
    WeightMap weight_map;
};

// Classe per grafi diretti ponderati
class SimpleWeightedDirectedGraph : public SimpleWeightedGraphBase<boost::directedS> {
    public:
        using Base = SimpleWeightedGraphBase<boost::directedS>;
        using Node = typename Base::Node;
    
        // Metodo per l'ordinamento topologico
        std::vector<Node> topological_sort() const {
            std::vector<Node> result;
            try {
                // Utilizzo della funzione topological_sort di Boost
                boost::topological_sort(this->g, std::back_inserter(result));
                // Invertiamo l'ordine poiché boost::topological_sort 
                // inserisce i nodi in ordine inverso
                std::reverse(result.begin(), result.end());
            } catch (const boost::not_a_dag& e) {
                std::cerr << "Error: Il grafo contiene cicli, impossibile effettuare l'ordinamento topologico.\n";
                // Svuotiamo il risultato in caso di errore
                result.clear();
            }
            return result;
        }
};

// Classe per grafi indiretti ponderati
class SimpleWeightedUndirectedGraph : public SimpleWeightedGraphBase<boost::undirectedS> {
    public:
        using Base = SimpleWeightedGraphBase<boost::undirectedS>;
        using Node = typename Base::Node;
};

// Alias per grafi non ponderati
using SimpleUnweightedDirectedGraph = SimpleDirectedGraph;
using SimpleUnweightedUndirectedGraph = SimpleUndirectedGraph;

#endif // NXPP_HPP