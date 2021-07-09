#include "tick.hpp"

constexpr double billion = 1000000000;
/**
 * @brief Construct a new tick::tick object record the curreng time to calculate the necessary sleep.
 * 
 * @param FPS 
 */
tick::tick(const int FPS) : FPS(FPS) , start(std::chrono::system_clock::now()) {}

tick::~tick() { 
    // how much time has passed since construction.
    const std::chrono::nanoseconds time_passed = std::chrono::system_clock::now() - start;
    // how much time was supposed to pass for one tick.
    const std::chrono::nanoseconds time_intended((long) (billion / FPS));
    // how much time still needs to pass.
    const std::chrono::nanoseconds wait_time = time_intended - time_passed;

    // wait until tick done.
    std::this_thread::sleep_for(wait_time);
}