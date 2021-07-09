#include "coordinates.hpp"

/**
 * @brief return a coordinates one step towards dir direction, if we move passed the side switch to the other one.
 * 
 * @param dir 
 * @param corner 
 * @return coordinates 
 */
coordinates coordinates::move(const direction dir, const coordinates corner)    const {
    switch (dir)    {
        case LEFT:
            // if moving left does not go out of bounds, return the left coordinates
            if (this -> x - 1 >= 0)
                return {this -> x - 1, this -> y};
            // if out of bounds, return the right side.
            else
                return {corner.x - 1, this -> y};
            break;
        
        // same as left but right.
        case RIGHT:
            if (this -> x + 1 < corner.x)
                return {this -> x + 1, this -> y};
            else 
                return {0, this -> y};
            break;
        
        //...
        case DOWN:
            if (this -> y + 1 < corner.y)
                return {this -> x, this -> y + 1};
            else
                return {this -> x, 0};
            break;
        
        //...
        case UP:
            if (this -> y - 1 >= 0)
                return {this -> x, this -> y - 1};
            else 
                return {this -> x, corner.y - 1};
            break;
    }

    // unreachable
    return {0, 0};
}

/**
 * @brief create a coordinate limited by corner, if passed corner push it in assuming a rotation by corner.
 * 
 * @param corner 
 * @return coordinates 
 */
coordinates coordinates::limit(const coordinates & corner)  const {
    coordinates limited = {this -> x % corner.x, this -> y % corner.y};

    if (limited.x < 0)
        limited.x += corner.x;
    if (limited.y < 0)
        limited.y += corner.y;

    return limited;
}

/**
 * @brief create a random coordinate bounded by "this"
 * 
 * @return coordinates 
 */
coordinates coordinates::random_in_bound()  const {
    static std::default_random_engine generator(time(NULL));
    static std::uniform_int_distribution<int> distribution_x(0, this -> x - 1);
    static std::uniform_int_distribution<int> distribution_y(0, this -> y - 1);

    return {distribution_x(generator), distribution_y(generator)};
}

/**
 * @brief print a char in window in "this" coordinates
 * 
 * @param win 
 * @param c 
 */
void coordinates::print(WINDOW * win, const char c) const {
    // print at y + 1, x + 1 because there is a border in window.
    mvwprintw(win, this -> y + 1, this -> x + 1, "%c", c);
}

/**
 * @brief print a c string in window in "this" coordinates
 * 
 * @param win 
 * @param s 
 */
void coordinates::print(WINDOW * win, const char *s) const {
    // print at y + 1, x + 1 because there is a border in window.
    mvwprintw(win, this -> y + 1, this -> x + 1, "%s", s);
}

bool coordinates::operator==(const coordinates & other) const {
    return this -> x == other.x && this -> y == other.y;
}

bool coordinates::operator!=(const coordinates & other) const {
    return !(*this == other);
}

/**
 * @brief return a coordinate representing the difference between this and other.
 * 
 * @param other 
 * @return coordinates 
 */
coordinates coordinates::operator-(const coordinates & other) const {
    return {this -> x - other.x, this -> y - other.y};
}

/**
 * @brief return a coordinate representing the sum with this and other.
 * 
 * @param other 
 * @return coordinates with sum x and sum y 
 */
coordinates coordinates::operator+(const coordinates & other) const {
    return {this -> x + other.x, this -> y + other.y};
}
