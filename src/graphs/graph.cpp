# include "graph.hpp"

# include <fstream>
# include <iostream>
# include <sstream>
# include <stdexcept>

Graph::Graph(const std::string& filename){
    loadFromFile(filename);
}

void Graph::loadFromFile(const std::string& filename) {
    adjacencyMatrix.clear();

    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error(
            "Could not open graph file: " + filename
        );
    }

    std::string line;

    while (std::getline(file, line)){
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        std::vector<int> row;
        std::string value;

        while (std::getline(ss, value, ',')) {
            row.push_back(std::stoi(value));
        }
        adjacencyMatrix.push_back(row);
    }

    if (adjacencyMatrix.empty()) {
        throw std::runtime_error(
            "Adjacency matrix is empty."
        );
    }

    const size_t n = adjacencyMatrix.size();
    for (const auto& row : adjacencyMatrix) {
        if (row.size() != n) {
            throw std::runtime_error(
                "Adjacency matrix must be square."
            );
        }
    }
}

int Graph::size() const {
    return static_cast<int>(adjacencyMatrix.size());
}

int Graph::degree(int vertex) const {
    int count = 0;

    for (int value : adjacencyMatrix[vertex]) {
        if (value == 1) {
            count++;
        }
    }
    return count;
}

std::vector<int> Graph::getNeighbors(int vertex) const {
    std::vector<int> neighbors;

    for (size_t i = 0; i < adjacencyMatrix[vertex].size(); ++i) {
        if (adjacencyMatrix[vertex][i] == 1) {
            neighbors.push_back(static_cast<int>(i));
        }
    }
    return neighbors;
}

bool Graph::hasEdge(int u, int v) const {
    return adjacencyMatrix[u][v] == 1;
}

void Graph::print() const {
    std::cout << "Adjacency Matrix:" << std::endl;

    for (const auto& row : adjacencyMatrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Number of vertices: " << size() << std::endl;
}
