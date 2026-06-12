#pragma once

#include "drinking_strategy.hpp"

/**
 * @brief Deadlock-free strategy based on resource ordering.
 *
 * Bottles are always acquired in ascending ID order, enforcing a global
 * lock hierarchy that eliminates circular wait conditions.
 */
class OrderedStrategy : public DrinkingStrategy {
    public:
        /**
         * @brief Acquires bottles sorted by ascending ID, locking each in order.
         * Prevents deadlock by ensuring all philosophers compete for resources
         * in the same global sequence.
         */
        void acquireResources(
            Philosopher& philosopher,
            const std::vector<Bottle*>& bottles
        ) override;

        /**
         * @brief Releases all bottles (in ascending ID order).
         */
        void releaseResources(
            Philosopher& philosopher,
            const std::vector<Bottle*>& bottles
        ) override;
};