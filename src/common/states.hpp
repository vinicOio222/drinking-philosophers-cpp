#pragma once 

/**
 * @brief Enum representing the state of a philosopher.
 * @param THINKING the philosopher is thinking and not trying to drink.
 * @param THIRSTY the philosopher is trying to drink but has not yet acquired 
 *                all the necessary bottles.
 * @param DRINKING the philosopher has acquired all the necessary bottles and is drinking.
 */
enum class State {
    THINKING,
    THIRSTY,
    DRINKING
};
