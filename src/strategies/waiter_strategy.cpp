#include "waiter_strategy.hpp"
#include "../resources/bottle.hpp"

// Wait until ALL required bottles are simultaneously free, then reserve them.
// The all-or-nothing check inside the predicate prevents partial acquisition,
// which would otherwise allow deadlock between competing philosophers.
void WaiterStrategy::acquireResources(
    Philosopher& philosopher, const std::vector<Bottle*>& bottles
) {
    std::unique_lock<std::mutex> lock(mtx);

    condVar.wait(lock, [&] {
        for (auto* bottle : bottles) {
            if (inUse.count(bottle->getId())) return false;
        }
        return true;
    });

    for (auto* bottle : bottles) {
        inUse.insert(bottle->getId());
    }
}

void WaiterStrategy::releaseResources(
    Philosopher& philosopher, const std::vector<Bottle*>& bottles
) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto* bottle : bottles) {
            inUse.erase(bottle->getId());
        }
    }
    condVar.notify_all();
}