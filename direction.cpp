#include "direction.hpp"

/**
 * @brief switch up to down, down to up, left to right, and right to left. 
 * 
 * @param dir 
 * @return direction 
 */
direction operator!(const direction dir)  {
    
    switch (dir)    {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
        
        // impossible
        default:
            return UP;
    }
}