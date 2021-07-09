#ifndef DIRECTION_HPP
#define DIRECTION_HPP

enum direction {LEFT, RIGHT, DOWN, UP};

/**
 * @brief switches direction (up to down and left to right)
 * 
 * @param dir 
 * @return direction 
 */
direction operator!(const direction dir);

#endif // _DIRECTION_HPP_
