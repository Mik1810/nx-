#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>

class SimpleGraph {
public:
    using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
    using Node = boost::graph_traits<GraphType>::vertex_descriptor;
    using Edge = boost::graph_traits<GraphType>::edge_descriptor;

    // Costruttore
    SimpleGraph() : g(), next_id(0) {}

    // Aggiungi un nodo
    Node add_node() {
        Node v = boost::add_vertex(g);
        node_attrs[v] = {};  // inizializza attributi vuoti
        return v;
    }

    void add_nodes(int number_of_nodes) {
        for(Node i = 0; i < number_of_nodes; i++) 
            add_node();
    }

    // G.add_nodes_from([2, 3])
    void add_nodes_from(std::vector<Node> nodes) {
        for (Node node : nodes) {
            add_node();
        }
    }

    Edge add_edge(Node i, Node j) {
        return boost::add_edge(i, j, g).first;
    }

    void add_edges_from(std::vector<std::pair<Node, Node>> edges) {
        for(std::pair<Node, Node> edge : edges) {
            add_edge(edge.first, edge.second);
        }
    }    

    // Restituisce la lista dei nodi
    std::vector<Node> nodes() const {
        std::vector<Node> result;
        for (auto [v, vend] = boost::vertices(g); v != vend; ++v)
            result.push_back(*v);
        return result;
    }

    // Restituisce la lista degli archi
    std::vector<std::pair<Node, Node>> edges() const {
        std::vector<std::pair<Node, Node>> result;
        for (auto [e, eend] = boost::edges(g); e != eend; ++e)
            result.emplace_back(boost::source(*e, g), boost::target(*e, g));
        return result;
    }

    // Imposta un attributo di un nodo
    void set_node_attr(Node n, const std::string& key, const std::string& value) {
        node_attrs[n][key] = value;
    }

    // Recupera un attributo di un nodo
    std::string get_node_attr(Node n, const std::string& key) const {
        auto it = node_attrs.find(n);
        if (it != node_attrs.end()) {
            auto attr_it = it->second.find(key);
            if (attr_it != it->second.end()) {
                return attr_it->second;
            }
        }
        return "";
    }

    std::vector<Node> neighbors(Node* v) {
        std::vector<Node> result;
        for (auto [neighbor, end] = boost::adjacent_vertices(*v, g); neighbor != end; ++neighbor) {
            result.push_back(*neighbor);
        }
        return result;
    }



private:
    GraphType g;
    int next_id;
    std::unordered_map<Node, std::unordered_map<std::string, std::string>> node_attrs;
};
#endif // SIMPLEGRAPH_H

#ifndef SIMPLEWEIGHTEDGRAPH_H
#define SIMPLEWEIGHTEDGRAPH_H

// Funzione di hash personalizzata per Edge
namespace std {
    template <>
    struct hash<boost::detail::edge_desc_impl<boost::directed_tag, long unsigned int>> {
        std::size_t operator()(const boost::detail::edge_desc_impl<boost::directed_tag, long unsigned int>& edge) const {
            std::size_t seed = 0;
            boost::hash_combine(seed, edge.m_source);
            boost::hash_combine(seed, edge.m_target);
            return seed;
        }
    };
}

#ifndef TRIPLE_HPP
#define TRIPLE_HPP

template <typename T1, typename T2, typename T3>
struct Triple {
    T1 first;
    T2 second;
    T3 third;

    Triple(T1 f, T2 s, T3 t) : first(f), second(s), third(t) {}
};

#endif // TRIPLE_HPP

class SimpleWeightedGraph : public SimpleGraph {
    public:
        using GraphType = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                          boost::no_property, boost::property<boost::edge_weight_t, double>>;
        using Node = boost::graph_traits<GraphType>::vertex_descriptor;
        using Edge = boost::graph_traits<GraphType>::edge_descriptor;
        using weight_map = boost::property_map<GraphType, boost::edge_weight_t>::type;
    
        // Costruttore
        SimpleWeightedGraph() : g(), weight_map_(boost::get(boost::edge_weight, g)) {}
    
        // Aggiungi un arco con peso
        Edge add_edge(Node i, Node j, double weight) {
            Edge e = boost::add_edge(i, j, g).first;
            weight_map_[e] = weight;
            return e;
        }

        void add_edges_from(std::vector<Triple<Node, Node, double>> edges) {
            for (const auto& edge : edges) {
                add_edge(edge.first, edge.second, edge.third);
            }
        }

        // Restituisce la lista degli archi con i pesi
        std::vector<Triple<Node, Node, double>> edges() const {
            std::vector<Triple<Node, Node, double>> result;
            for (auto [e, eend] = boost::edges(g); e != eend; ++e) {
                result.emplace_back(boost::source(*e, g), boost::target(*e, g), weight_map_[*e]);
            }
            return result;
        }

        // Not a DAG
        // std::vector<Node> topological_sort() {
        //     std::vector<Node> sorted_nodes;
        //     boost::topological_sort(g, std::back_inserter(sorted_nodes));
        //     return sorted_nodes;
        // }

        std::pair<std::vector<Node>, std::vector<double>> dijkstra(Node v) {
            std::vector<double> dist(boost::num_vertices(g), std::numeric_limits<double>::infinity());
            std::vector<Node> pred(boost::num_vertices(g));
            boost::dijkstra_shortest_paths(g, v,
                boost::distance_map(boost::make_iterator_property_map(dist.begin(), boost::get(boost::vertex_index, g)))
                .predecessor_map(boost::make_iterator_property_map(pred.begin(), boost::get(boost::vertex_index, g))));
            return {pred, dist};
        }
    
    private:
        GraphType g;
        weight_map weight_map_;
};

#endif // SIMPLEGRAPH_H
