#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <ctime>
#include <string>
#include <ncurses.h>
#include <sstream>
#include <iomanip>

#include "snake.hpp"
#include "tick.hpp"
#include "food.hpp"
#include "direction.hpp"

using namespace std::chrono_literals;

constexpr int SNAKE_START_SIZE = 20;
constexpr int WIDTH = 100;
constexpr int HEIGHT = 25;
constexpr std::chrono::seconds FOOD_TIMEOUT = 8s;
constexpr int RED = 1;
constexpr int FPS = 20;

#endif // MAIN_HPP
