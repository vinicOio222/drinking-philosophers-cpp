#pragma once

#include "drinking_strategy.hpp"

#include <mutex>
#include <condition_variable>
#include <unordered_set>

/**
 * @brief Deadlock-free strategy using a centralized waiter (arbiter).
 *
 * A single monitor tracks which bottles are currently in use.
 * A philosopher only proceeds when all its required bottles are free,
 * using a condition variable to avoid busy-waiting.
 */
class WaiterStrategy : public DrinkingStrategy {
    private:
        std::mutex mtx;                      ///< Protects access to the inUse set.
        std::condition_variable condVar;     ///< Signals when bottles become available.
        std::unordered_set<int> inUse;       ///< IDs of bottles currently held by philosophers.

    public:
        /**
         * @brief Waits until all required bottles are free, then marks them as in use.
         * Atomically checks and reserves all bottles to prevent partial acquisition.
         */
        void acquireResources(
            Philosopher& philosopher,
            const std::vector<Bottle*>& bottles
        ) override;

        /**
         * @brief Releases all held bottles and notifies waiting philosophers.
         */
        void releaseResources(
            Philosopher& philosopher,
            const std::vector<Bottle*>& bottles
        ) override;
};
