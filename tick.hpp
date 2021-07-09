#ifndef TICK_HPP
#define TICK_HPP

#include <chrono>
#include <thread>
/**
 * @brief construct this in top of scope, on destruction an bottom of scope
 * will ensure the time was 1 / FPS.
 */
class tick {
public:
    tick(const int FPS = 60);
    ~tick();

private:
    const int FPS;
    const std::chrono::system_clock::time_point start;
};


#endif // TICK_HPP
