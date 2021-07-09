#include "food.hpp"

constexpr int billion = 1000000000;

Food::Food(WINDOW * win, coordinates corner, Snake & snake, std::chrono::seconds time, std::chrono::seconds tick_time) :
win(win), corner(corner), time(time), tick_time(tick_time) {
    this -> generate(snake);
}

Food::Food(WINDOW * win, coordinates corner, coordinates location, Snake & snake, std::chrono::seconds time, std::chrono::seconds tick_time) :
win(win), corner(corner), location(location), time(time), tick_time(tick_time), start(std::chrono::system_clock::now()) {}

/**
 * @brief checks if food is on other location.
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Food::collision(coordinates other)  {
    return this -> location == other;
}

/**
 * @brief print the food.
 * 
 */
void Food::print()    {
    // time passed since last food generation
    const std::chrono::nanoseconds time_passed = std::chrono::system_clock::now() - start;

    // time since food was created in seconds, needs to print in color if odd number of seconds.
    const int seconds_passed = time_passed.count() / billion;

    // on every second secend print in color.
    if (seconds_passed / tick_time.count() % 2 == 1)    {
        wattron(this -> win, COLOR_PAIR(1));
        this -> location.print(this -> win, '*');
        wattroff(this -> win, COLOR_PAIR(1));
    }
    else 
        this -> location.print(this -> win, '*');
}

/**
 * @brief generate the food object not on snake, reset the timer 
 * 
 * @param snake 
 */
void Food::generate(Snake & snake) {
    this -> start = std::chrono::system_clock::now();
    // generate radom location while location not in snake body (head is ok).
    while ((this -> location = this -> corner.random_in_bound()) 
            != snake.head() && snake.collides(this -> location));
}

/**
 * @brief check and handle if food is eaten, needs to move, or change color.
 * 
 * @param snake 
 */
void Food::tick(Snake & snake)   {
    // time since food was deployed in nanoseconds.
    const std::chrono::nanoseconds time_passed = std::chrono::system_clock::now() - start;

    // if food is eaten
    if (this -> collision(snake.head()))   {
        // recreate the food, and grow the snake.
        snake.grow();
        this -> generate(snake);
    }
    // if food timeout (needs to relocate)
    else if (time_passed > time)    {
        // delete the food and recreate it.
        this -> location.print(this -> win, ' ');
        generate(snake);
    }
}
