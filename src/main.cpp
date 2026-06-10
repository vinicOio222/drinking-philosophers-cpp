# include "graphs/graph.hpp"
# include <iostream>

int main() {
    Graph graph("case.txt");
    graph.print();

    std::cout << "Graph size: " << graph.size() << std::endl;
    std::cout << "Degree of vertex 0: " << graph.degree(0) << std::endl;

    return 0;

}