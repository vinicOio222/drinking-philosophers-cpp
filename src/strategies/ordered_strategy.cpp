#include "ordered_strategy.hpp"
#include "../resources/bottle.hpp"

#include <algorithm>

// Acquire bottles in ascending ID order to enforce a global lock hierarchy.
// This breaks circular wait: if every philosopher requests resources in the
// same order, no cycle can form in the wait-for graph.
void OrderedStrategy::acquireResources(
    Philosopher&, const std::vector<Bottle*>& bottles
){
    auto orderedBottles = bottles;
    std::sort(
        orderedBottles.begin(), 
        orderedBottles.end(),
        [](Bottle* a, Bottle* b) {
            return a->getId() < b->getId();
        }
    );

    for (auto* bottle : orderedBottles) {
        bottle->getMutex().lock();
    }
}

void OrderedStrategy::releaseResources(
    Philosopher&, const std::vector<Bottle*>& bottles
){
    auto orderedBottles = bottles;
    std::sort(
        orderedBottles.begin(),
        orderedBottles.end(),
        [](Bottle* a, Bottle* b){
            return a->getId() < b->getId();
        }
    );

    for (auto* bottle : orderedBottles) {
        bottle->getMutex().unlock();
    }
}
