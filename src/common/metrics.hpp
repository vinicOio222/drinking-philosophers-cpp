#pragma once

/**
 * @brief Struct to hold metrics for a philosopher's activities.
 * @param thinkingTime total time spent thinking.
 * @param thirstyTime total time spent trying to acquire bottles.
 * @param drinkingTime total time spent drinking.
 * @param drinksCompleted total number of times the philosopher has successfully drunk.
 */
struct Metrics {
    double thinkingTime = 0.0;
    double thirstyTime = 0.0;
    double drinkingTime = 0.0;
    int drinksCompleted = 0;
};
