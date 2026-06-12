#pragma once

#include <mutex>

/**
 * @brief A class representing a bottle in the drinking philosophers problem.
 * Each bottle is shared between two philosophers and has a unique ID.
 * @param id The unique identifier for the bottle.
 * @param philosopherA The ID of the first philosopher sharing the bottle.
 * @param philosopherB The ID of the second philosopher sharing the bottle.
 */
class Bottle{
    private:
        int id;
        int philosopherA;
        int philosopherB;

        std::mutex mtx;

    public:
        /**
         * @brief Constructs a Bottle with the given IDs.
         * @param id The unique identifier for the bottle.
         * @param philosopherA The ID of the first philosopher sharing the bottle.
         * @param philosopherB The ID of the second philosopher sharing the bottle.
         */
        Bottle(int id, int philosopherA, int philosopherB);
        /**
         * @brief Returns the unique identifier of the bottle.
         * @return The bottle's ID.
         */
        int getId() const;
        /**
         * @brief Returns the ID of the first philosopher sharing the bottle.
         * @return The ID of philosopher A.
         */
        int getPhilosopherA() const;
        /**
         * @brief Returns the ID of the second philosopher sharing the bottle.
         * @return The ID of philosopher B.
         */
        int getPhilosopherB() const;
        /**
         * @brief Returns a reference to the mutex associated with the bottle.
         * This mutex is used to synchronize access to the bottle between philosophers.
         * @return A reference to the bottle's mutex.
         */
        std::mutex& getMutex();
};