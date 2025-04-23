#ifndef EDGE_TRIPLE_HPP
#define EDGE_TRIPLE_HPP

// Struttura Triple per rappresentare un arco pesato
template <typename T1, typename T2, typename T3>
struct EdgeTriple {
    T1 first;
    T2 second;
    T3 weight;
    
    EdgeTriple(T1 f, T2 s, T3 w) : first(f), second(s), weight(w) {}
};

#endif // EDGE_TRIPLE_HPP