#include "snake.hpp"

Snake::Snake(WINDOW * win, coordinates position, coordinates corner, int size) : 
win(win), corner(corner) , dir(RIGHT) 
{
    this -> snake_body.push_front(position);
    // grow the snake to size length
    for (int i = 0; i < size - 1; i++)
        this -> grow();
}

Snake::Snake(WINDOW * win, int x, int y, int max_x, int max_y, int size) : 
    Snake(win, {x , y}, {max_x, max_y}, size) {}

Snake::Snake(WINDOW * win, coordinates position, int max_x, int max_y, int size) : 
    Snake(win, position, {max_x, max_y}, size) {}

Snake::Snake(WINDOW * win, coordinates corner, int size) : 
    Snake(win, {corner.x / 2, corner.y / 2}, corner, size) {}

/**
 * @brief move the snake in this -> dir.
 * 
 * @return true if movement is successfull (no self collitions)
 */
bool Snake::move()    {
    const coordinates head = this -> snake_body.front();   
    // where the head will be after movement. 
    const coordinates new_location = head.move(this -> dir, corner);   


    // if new location collides with self, movement fails.
    if (this -> collides_not_tail(new_location))
        return false;

    // erase the last snake cell from the screen.
    this -> snake_body.back().print(this -> win, ' ');

    // erase the last snake cell, and add a new head, to simulate moving.
    this -> snake_body.pop_back();
    this -> snake_body.push_front(new_location);

    return true;
}

/**
 * @brief move the snake in dir direction.
 * 
 * @param dir the direction to move the snake.
 * @return snake moved successfully
 */
bool Snake::move(direction dir) {
    this -> set_direction(dir);
    return this -> move();
}

/**
 * @brief move in dir direction, and print the snake.
 * 
 * @param dir 
 * @return snake moved successfully
 */
bool Snake::tick(const direction dir) {
    return  this -> move(dir);
}

/**
 * @brief move in the last movement direction, and print the snake.
 * 
 * @return true if movement was successful
 * @return false otherwise
 */
bool Snake::tick() {
    return this -> tick(this -> dir);
}

/**
 * @brief checks if position is on the snake body
 * 
 * @param position 
 * @return true if position is on the snake
 * @return false otherwise
 */
bool Snake::collides(const coordinates position)  const {
    // iterate on snake check if coordinates in it's body
    for (auto & pos : this -> snake_body)   {
        if (pos == position)
            return true;
    }

    return false;
}

/**
 * @brief set the snake movement direction if leagal
 * 
 * @param dir 
 */
void Snake::set_direction(direction dir)    {
    // if not trying to move backwords
    if ((this -> snake_body.front().move(dir, this -> corner))
     != (this -> snake_body.begin().operator++().operator*()))
        this -> dir = dir;
}

/**
 * @brief grow the snake by appending to the tail.
 * 
 */
void Snake::grow()  {
    const coordinates tail_location = this -> snake_body.back();

    // if there is a snake body except for the tail, grow in the direction of the tail
    if (this -> snake_body.size() > 1)  {        
        // coordinates of the node before the last.
        const coordinates pre_tail_location = this -> snake_body.rbegin().operator++().operator*();
        // create a tail at the location continuing the line between tail and pre tail.
        this -> snake_body.push_back((tail_location - (pre_tail_location - tail_location)).limit(corner));
    }
    else {
        // continue the tail based on the opposite movement direction.
        coordinates tail_location_copy = {tail_location.x, tail_location.y};
        this -> snake_body.push_back(tail_location_copy.move(!(this -> dir), this -> corner));
    }
}

/**
 * @brief return the number of cells in the snake, AKA the number of nodes in the list.
 * 
 * @return size of the snake
 */
int Snake::size()  const {
    return this -> snake_body.size();
}

/**
 * @brief print the snake to the screen using 'o' character for the body
 * 
 */
void Snake::print() const {
    // for each node location print it.
    for (auto pos : this -> snake_body) {
        pos.print(this -> win, 'o');
    }
}

/**
 * @brief get the head location.
 * 
 * @return coordinated of head  
 */
coordinates Snake::head()  const {
    return this -> snake_body.front();
}

bool Snake::collides_not_tail(coordinates location) const {
    return this -> collides(location) && location != this -> snake_body.back();
}