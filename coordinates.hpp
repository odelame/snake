#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include <ncurses.h>
#include <random>
#include "direction.hpp"
#include <ctime>

/**
 * @brief represend a coordinates on a graph.
 */
struct coordinates {
    int x;
    int y;

    bool operator==(const coordinates& other) const;
    bool operator!=(const coordinates& other) const;

    coordinates operator-(const coordinates& other) const;

    coordinates operator+(const coordinates& other) const;

    coordinates move(const direction dir, const coordinates corner) const;
    coordinates limit(const coordinates& corner) const;
    coordinates random_in_bound() const;

    void print(WINDOW* win, const char c) const;
    void print(WINDOW* win, const char* s) const;
};

#endif // COORDINATES_HPP
