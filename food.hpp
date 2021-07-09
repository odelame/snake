#ifndef FOOD_HPP
#define FOOD_HPP

#include "coordinates.hpp"
#include "snake.hpp"
#include <chrono>

using namespace std::chrono_literals;

class Food {
public:
    /**
     * @brief Construct a new Food object
     *
     * @param win the window to draw on
     * @param corner max x,y of the window
     * @param snake the snake the food interacts with
     * @param time duration until food timeouts
     * @param tick_time ticking time for food to change color
     */
    Food(WINDOW* win, coordinates corner, Snake& snake,
        std::chrono::seconds time = 10s, std::chrono::seconds tick_time = 1s);

    /**
     * @brief Construct a new Food object
     *
     * @param win the window to draw on
     * @param corner max x,y of the window
     * @param location beginning location of the food
     * @param snake the snake the food interacts with
     * @param time duration until food timeouts
     * @param tick_time ticking time for food to change color
     */
    Food(WINDOW* win, coordinates corner, coordinates location, Snake& snake,
        std::chrono::seconds time = 10s, std::chrono::seconds tick_time = 1s);

    /**
     * @brief check if the foods coordinates are equal to other coordinates.
     *
     * @param other
     * @return true
     * @return false
     */
    bool collision(coordinates other);
    /**
     * @brief print the food.
     *
     */
    void print();
    /**
     * @brief change food color or position of the food and print.
     *
     * @param snake
     */
    void tick(Snake& snake);
private:

    /**
     * @brief generates a food position which is not on snake.
     *
     * @param snake
     */
    void generate(Snake& snake);

    WINDOW* win;
    const coordinates corner;
    coordinates location;
    const std::chrono::seconds time;
    const std::chrono::seconds tick_time;

    std::chrono::system_clock::time_point start;
};

#endif // FOOD_HPP
