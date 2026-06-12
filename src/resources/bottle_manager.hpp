#pragma once

#include "../graphs/graph.hpp"
#include "bottle.hpp"

#include <memory>
#include <vector>

/**
 * @brief A class responsible for managing the bottles in the drinking philosophers problem.
 * It initializes the bottles based on the graph structure and provides methods to retrieve
 * the bottles and their associations with philosophers.
 * @param graph The graph representing the relationships between philosophers and bottles.
 */
class BottleManager {
    private:
        std::vector<std::unique_ptr<Bottle>> bottles;

    public:
        /**
         * @brief Constructs a BottleManager based on the given graph.
         * @param graph The graph representing the relationships between philosophers and bottles.
         */
        explicit BottleManager(const Graph& graph);

        /**
         * @brief Returns a constant reference to the vector of bottles managed by the BottleManager.
         * @return A constant reference to the vector of unique pointers to Bottle objects.
         */
        const std::vector<std::unique_ptr<Bottle>>& getBottles() const;

        /**
         * @brief Returns a vector of raw pointers to the bottles adjacent to a given philosopher.
         * @param philosopherId The ID of the philosopher for whom to retrieve adjacent bottles.
         * @return A vector of raw pointers to the adjacent Bottle objects.
         */
        std::vector<Bottle*> getBottlesForPhilosopher(
            int philosopherId
        ) const;
};
