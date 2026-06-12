#include "graphs/graph.hpp"
#include "resources/bottle_manager.hpp"
#include "philosophers/philosopher.hpp"
#include "strategies/ordered_strategy.hpp"
#include "strategies/waiter_strategy.hpp"
#include "common/logger.hpp"

#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <iomanip>

/**
 * @brief Prints the metrics report for a given strategy.
 *
 * @param strategyName Name of the synchronization strategy.
 * @param philosophers Vector of philosopher objects.
 * @param simulationTime Total simulation time in seconds.
 */
static void printMetricsReport(
    const std::string& strategyName,
    const std::vector<std::unique_ptr<Philosopher>>& philosophers,
    double simulationTime
) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(3);

    out << "\n--- Metrics: " << strategyName << " ---\n";
    out << std::left
        << std::setw(12) << "Philosopher"
        << std::setw(14) << "Thinking(s)"
        << std::setw(13) << "Thirsty(s)"
        << std::setw(13) << "Drinking(s)"
        << std::setw(8)  << "Drinks"
        << std::setw(16) << "Avg Wait(s)"
        << '\n';
    out << std::string(76, '-') << '\n';

    double totalThirsty = 0.0;
    int totalDrinks = 0;

    for (const auto& p : philosophers) {
        const Metrics& m = p->getMetrics();
        double avgWait = m.drinksCompleted > 0
            ? m.thirstyTime / m.drinksCompleted
            : 0.0;

        out << std::setw(12) << p->getId()
            << std::setw(14) << m.thinkingTime
            << std::setw(13) << m.thirstyTime
            << std::setw(13) << m.drinkingTime
            << std::setw(8)  << m.drinksCompleted
            << std::setw(16) << avgWait
            << '\n';

        totalThirsty += m.thirstyTime;
        totalDrinks  += m.drinksCompleted;
    }

    int n = static_cast<int>(philosophers.size());
    out << std::string(76, '-') << '\n';
    out << "Total simulation time : " << simulationTime << " s\n";
    out << "Total drinks completed: " << totalDrinks << '\n';
    out << "Avg thirsty time      : " << (n > 0 ? totalThirsty / n : 0.0) << " s\n";

    Logger::write(out.str());
}

/**
 * @brief Runs a test case with the specified parameters.
 * @param caseFile Path to the case file.
 * @param caseNumber Case number.
 * @param maxDrinks Maximum number of drinks per philosopher.
 */
static void runCase(
    const std::string& caseFile,
    int caseNumber,
    int maxDrinks
) {
    std::ostringstream hdr;
    hdr << "\n\n========================================\n"
        << "=== CASE " << caseNumber << " : " << caseFile
        << " (" << maxDrinks << " drinks each) ===\n"
        << "========================================\n";
    Logger::write(hdr.str());

    Graph graph(caseFile);

    std::ostringstream graphOut;
    graphOut << "\n=== GRAPH ===\n";
    Logger::write(graphOut.str());
    graph.print();

    BottleManager manager(graph);

    std::ostringstream bottlesOut;
    bottlesOut << "\n=== BOTTLES ===\n";
    for (const auto& bottle : manager.getBottles()) {
        bottlesOut
            << "Bottle " << bottle->getId()
            << " : " << bottle->getPhilosopherA()
            << " <-> " << bottle->getPhilosopherB()
            << '\n';
    }
    Logger::write(bottlesOut.str());

    // --- Ordered Strategy ---
    Logger::write("\n=== THREAD TEST (Ordered Strategy) ===\n");
    {
        OrderedStrategy strategy;
        std::vector<std::unique_ptr<Philosopher>> philosophers;

        for (int i = 0; i < graph.size(); i++) {
            philosophers.push_back(
                std::make_unique<Philosopher>(
                    i,
                    manager.getBottlesForPhilosopher(i),
                    &strategy,
                    maxDrinks
                )
            );
        }

        auto orderedStart = std::chrono::steady_clock::now();
        for (auto& p : philosophers) p->start();
        for (auto& p : philosophers) p->join();
        double orderedElapsed = std::chrono::duration<double>(
            std::chrono::steady_clock::now() - orderedStart
        ).count();

        printMetricsReport("Ordered Strategy", philosophers, orderedElapsed);
    }

    // --- Waiter Strategy ---
    Logger::write("\n=== THREAD TEST (Waiter Strategy) ===\n");
    {
        WaiterStrategy waiterStrategy;
        std::vector<std::unique_ptr<Philosopher>> philosophers;

        for (int i = 0; i < graph.size(); i++) {
            philosophers.push_back(
                std::make_unique<Philosopher>(
                    i,
                    manager.getBottlesForPhilosopher(i),
                    &waiterStrategy,
                    maxDrinks
                )
            );
        }

        auto waiterStart = std::chrono::steady_clock::now();
        for (auto& p : philosophers) p->start();
        for (auto& p : philosophers) p->join();
        double waiterElapsed = std::chrono::duration<double>(
            std::chrono::steady_clock::now() - waiterStart
        ).count();

        printMetricsReport("Waiter Strategy", philosophers, waiterElapsed);
    }
}

/**
 * @brief Main entry point of the program.
 * Initializes the logger, runs all test cases, and handles exceptions.
 */
int main() {
    Logger::init("results.txt");

    try {
        runCase("case1.txt", 1, 6);
        runCase("case2.txt", 2, 6);
        runCase("case3.txt", 3, 3);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        Logger::close();
        return 1;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        Logger::close();
        return 1;
    }

    Logger::close();
    return 0;
}