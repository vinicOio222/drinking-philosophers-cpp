#include "bottle_manager.hpp"

BottleManager::BottleManager(const Graph& graph) {
    int bottleId = 0;

    const int n = graph.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (graph.hasEdge(i, j)) {
                bottles.push_back(
                    std::make_unique<Bottle>(bottleId++, i, j)
                );
            }
        };
    }
}

const std::vector<std::unique_ptr<Bottle>>& BottleManager::getBottles() const {
    return bottles;
}

std::vector<Bottle*> BottleManager::getBottlesForPhilosopher(
    int philosopherId
) const {
    std::vector<Bottle*> result;

    for (const auto& bottle : bottles) {
        if (
            bottle->getPhilosopherA() == philosopherId || 
            bottle->getPhilosopherB() == philosopherId
        ) {
            result.push_back(bottle.get());
        };
    }
    return result;
}