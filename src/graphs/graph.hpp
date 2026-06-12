#pragma once

#include <vector>
#include <string>


/**
 * @brief Represents an undirected graph using an adjacency matrix.
 * Vertices represent philosophers; edges represent shared bottles.
 */
class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
    
    public:
        /** @brief Constructs an empty Graph. */
        Graph() = default;

        /**
         * @brief Constructs a Graph by loading its adjacency matrix from a file.
         * @param filename Path to a CSV-formatted adjacency matrix file.
         */
        explicit Graph(const std::string& filename);

        /**
         * @brief Loads (or reloads) the graph from a file.
         * @param filename Path to a CSV-formatted adjacency matrix file.
         */
        void loadFromFile(const std::string& filename);

        /**
         * @brief Returns the number of vertices in the graph.
         * @return Number of vertices.
         */
        int size() const;

        /**
         * @brief Returns the degree of a given vertex (number of adjacent edges).
         * @param vertex Index of the vertex.
         * @return Degree of the vertex.
         */
        int degree(int vertex) const;

        /**
         * @brief Returns the list of vertices adjacent to the given vertex.
         * @param vertex Index of the vertex.
         * @return Vector of neighbor indices.
         */
        std::vector<int> getNeighbors(int vertex) const;

        /**
         * @brief Checks whether an edge exists between two vertices.
         * @param u Index of the first vertex.
         * @param v Index of the second vertex.
         * @return True if the edge (u, v) exists.
         */
        bool hasEdge(int u, int v) const;

        /**
         * @brief Returns a string representation of the adjacency matrix.
         * @return Formatted string with the matrix and vertex count.
         */
        std::string toString() const;

        /** @brief Writes the adjacency matrix to the logger output. */
        void print() const;
};
