#include "philosopher.hpp"
#include "../strategies/drinking_strategy.hpp"
#include "../common/logger.hpp"

#include <chrono>
#include <thread>
#include <random>

Philosopher::Philosopher(
    int id,
    const std::vector<Bottle*>& bottles,
    DrinkingStrategy* strategy,
    int maxDrinks
) : id(id),
    state(State::THINKING), 
    adjacentBottles(bottles), 
    strategy(strategy), 
    maxDrinks(maxDrinks) {}

/**
 * @brief Returns the unique identifier of the philosopher.
 * @return The philosopher's ID.
 */
int Philosopher::getId() const {
    return id;
}

/**
 * @brief Returns the metrics of the philosopher.
 * @return A constant reference to the philosopher's metrics.
 */
const Metrics& Philosopher::getMetrics() const {
    return metrics;
}

/**
 * @brief Returns the metrics of the philosopher.
 * @return A reference to the philosopher's metrics.
 */
Metrics& Philosopher::getMetrics() {
    return metrics;
}

/**
 * @brief Returns the bottles adjacent to the philosopher.
 * @return A constant reference to the vector of adjacent bottles.
 */
const std::vector<Bottle*>& Philosopher::getBottles() const {
    return adjacentBottles;
}

/**
 * @brief Acquires the bottles adjacent to the philosopher.
 */
void Philosopher::acquireBottles() {
    strategy->acquireResources(*this, adjacentBottles);
}

/**
 * @brief Releases the bottles adjacent to the philosopher.
 */
void Philosopher::releaseBottles() {
    strategy->releaseResources(*this, adjacentBottles);
}

/**
 * @brief Starts the philosopher's thread to run the simulation.
 */
void Philosopher::start() {
    worker = std::thread(&Philosopher::run, this);
}
 

/**
 * @brief Joins the philosopher's thread, waiting for it to finish.
 */
void Philosopher::join() {
    if (worker.joinable()){
        worker.join();
    }
}


/**
 * @brief The main loop for the philosopher's actions.
 * @details The philosopher alternates between thinking, being thirsty, and drinking.
 * The philosopher will attempt to drink a specified number of times, acquiring and releasing bottles as needed.
 * The method also records the time spent in each state for metrics purposes.
 */
void Philosopher::run()
{
    thread_local std::mt19937 rng(std::random_device{}());

    for (int i = 0; i < maxDrinks; i++)
    {
        // THINKING
        state = State::THINKING;
        auto thinkingStart = std::chrono::steady_clock::now();

        Logger::log("Philosopher " + std::to_string(id) + " is thinking.");

        const int degree = static_cast<int>(adjacentBottles.size());
        std::uniform_int_distribution<int> dist(0, degree);
        std::this_thread::sleep_for(std::chrono::seconds(dist(rng)));

        auto thinkingEnd = std::chrono::steady_clock::now();
        metrics.thinkingTime += std::chrono::duration<double>(
            thinkingEnd - thinkingStart
        ).count();

        // THIRSTY
        state = State::THIRSTY;

        Logger::log("Philosopher " + std::to_string(id) + " is thirsty.");

        auto thirstyStart = std::chrono::steady_clock::now();

        acquireBottles();

        auto thirstyEnd = std::chrono::steady_clock::now();

        metrics.thirstyTime += std::chrono::duration<double>(
            thirstyEnd - thirstyStart
        ).count();
        
        // DRINKING
        state = State::DRINKING;
        auto drinkingStart = std::chrono::steady_clock::now();

        Logger::log("Philosopher " + std::to_string(id) + " is drinking.");

        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto drinkingEnd = std::chrono::steady_clock::now();
        metrics.drinkingTime += std::chrono::duration<double>(
            drinkingEnd - drinkingStart
        ).count();

        releaseBottles();

        metrics.drinksCompleted++;

        Logger::log(
            "Philosopher "
            + std::to_string(id)
            + " has completed drink #"
            + std::to_string(metrics.drinksCompleted)
            + "."
        );

    }
    state = State::THINKING;
}