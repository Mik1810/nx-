#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/topological_sort.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <tuple>

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
template <typename DirectedS, typename WeightType>
class SimpleWeightedGraphBase {
public:
    using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, DirectedS,
                                            boost::no_property, boost::property<boost::edge_weight_t, WeightType>>;
    using Node = typename boost::graph_traits<GraphType>::vertex_descriptor;
    using Edge = typename boost::graph_traits<GraphType>::edge_descriptor;
    using WeightMap = typename boost::property_map<GraphType, boost::edge_weight_t>::type;

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
        for (const auto& [u, v, weight] : edges) {
            add_edge(u, v, weight);
        }
    }

    std::vector<Node> nodes() const {
        std::vector<Node> result;
        for (auto [v, vend] = boost::vertices(g); v != vend; ++v) {
            result.push_back(*v);
        }
        return result;
    }

    std::vector<std::tuple<Node, Node, WeightType>> edges() const {
        std::vector<std::tuple<Node, Node, WeightType>> result;
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
template <typename WeightType>
class SimpleWeightedDirectedGraph : public SimpleWeightedGraphBase<boost::directedS, WeightType> {};

// Classe per grafi indiretti ponderati
template <typename WeightType>
class SimpleWeightedUndirectedGraph : public SimpleWeightedGraphBase<boost::undirectedS, WeightType> {};

// Alias per grafi non ponderati
using SimpleUnweightedDirectedGraph = SimpleDirectedGraph;
using SimpleUnweightedUndirectedGraph = SimpleUndirectedGraph;

#endif // SIMPLEGRAPH_H