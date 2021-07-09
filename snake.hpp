#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <list>
#include <ncurses.h>

#include "coordinates.hpp"
#include "direction.hpp"

/**
 * @brief Snake object has a list of coordinates for where the snake is.
 * Supports checks to see if the snake hit itself, printing, grow, and moving.
 */
class Snake {
public:
    Snake(WINDOW* win, int x, int y, int max_x, int max_y, int size = 1);
    Snake(WINDOW* win, coordinates position, int max_x, int max_y, int size = 1);
    Snake(WINDOW* win, coordinates position, coordinates corner, int size = 1);
    Snake(WINDOW* win, coordinates corner, int size = 1);

    // move the snake in dir direction or in previous direction.
    bool move(const direction dir);
    bool move();

    // move the snake, and print.
    bool tick(const direction dir);
    bool tick();

    void set_direction(const direction dir);
    void grow();

    void print() const;

    // checks if position is "on" the snake body.
    bool collides(const coordinates position) const;

    // get size of the snake (how many coordinates in the list)
    int size() const;

    // get head position.
    coordinates head() const;
private:
    // snake env.
    WINDOW* win;
    std::list<coordinates> snake_body;
    // corner of snake env (for max x and max y)
    const coordinates corner;
    direction dir;

    bool collides_not_tail(coordinates location) const;
};

#endif // SNAKE_HPP
