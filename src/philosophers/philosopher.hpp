#pragma once

#include "../common/metrics.hpp"
#include "../common/states.hpp"
#include "../resources/bottle.hpp"

#include <vector>
#include <thread>


class DrinkingStrategy; // Forward declaration to avoid circular dependency

/**
 * @brief A class representing a philosopher in the drinking philosophers problem.
 * @param id The unique identifier for the philosopher.
 * @param bottles A vector of pointers to the bottles adjacent to the philosopher.
 * @param strategy A pointer to the drinking strategy used by the philosopher.
 * @param maxDrinks The maximum number of drinks the philosopher will attempt to consume.
 */
class Philosopher{
    private:
        int id;
        State state;
        Metrics metrics;
        std::vector<Bottle*> adjacentBottles;
        DrinkingStrategy* strategy;
        std::thread worker;
        int maxDrinks;

    public:
        /**
         * @brief Constructs a Philosopher and associates it with a strategy.
         * @param id Unique identifier for the philosopher.
         * @param bottles Adjacent bottles (shared resources) this philosopher competes for.
         * @param strategy Synchronization strategy used to acquire/release bottles.
         * @param maxDrinks Number of times the philosopher will drink before finishing.
         */
        Philosopher(
            int id, const std::vector<Bottle*>& bottles, 
            DrinkingStrategy* strategy, int maxDrinks = 3
        );

        /** @brief Returns the philosopher's unique ID. */
        int getId() const;

        /** @brief Returns a const reference to the accumulated metrics. */
        const Metrics& getMetrics() const;

        /** @brief Returns a mutable reference to the accumulated metrics. */
        Metrics& getMetrics();

        /** @brief Returns the list of adjacent bottles. */
        const std::vector<Bottle*>& getBottles() const;

        /** @brief Acquires all adjacent bottles using the assigned strategy (blocks until granted). */
        void acquireBottles();

        /** @brief Releases all adjacent bottles using the assigned strategy. */
        void releaseBottles();

        /** @brief Launches the philosopher's thread (begins the think-thirsty-drink loop). */
        void start();

        /** @brief Blocks until the philosopher's thread completes all drinking sessions. */
        void join();

        /** @brief Thread entry point: executes the think → thirsty → drink cycle. */
        void run();
};