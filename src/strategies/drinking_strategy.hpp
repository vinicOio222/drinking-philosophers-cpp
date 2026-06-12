#pragma once

#include <vector>


class Bottle;
    class Philosopher;

/**
 * @brief Abstract base class for synchronization strategies.
 *
 * Defines the interface for acquiring and releasing shared bottles.
 * Concrete implementations must prevent deadlock and minimize starvation.
 */
class DrinkingStrategy {
    public:
        virtual ~DrinkingStrategy() = default;

        /**
         * @brief Acquires all required bottles for the philosopher.
         * Blocks until the strategy grants access to every bottle in the list.
         * @param philosopher The philosopher requesting the resources.
         * @param bottles The bottles the philosopher needs to drink.
         */
        virtual void acquireResources(
            Philosopher& philosopher,
            const std::vector<Bottle*>& bottles
        ) = 0;

        /**
         * @brief Releases all bottles held by the philosopher.
         * @param philosopher The philosopher releasing the resources.
         * @param bottles The bottles to be released.
         */
        virtual void releaseResources(
            Philosopher& philosopher,
            const std::vector<Bottle*>& bottles
        ) = 0;
};
