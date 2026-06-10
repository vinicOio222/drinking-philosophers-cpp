# pragma once

# include <vector>
# include <string>


class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
    
    public:
        Graph() = default;
        explicit Graph(const std::string& filename); 
        void loadFromFile(const std::string& filename);
        int size() const;
        int degree(int vertex) const;
        std::vector<int> getNeighbors(int vertex) const;
        bool hasEdge(int u, int v) const;
        void print() const;
};
