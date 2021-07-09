#include "main.hpp"

/**
 * @brief 
 * Sets the enviornment for ncurses, initializes everything so 
 * if we will change the code order, nothing will change.
 */
void startup()    {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    curs_set(0);

    start_color();
    init_pair(RED, COLOR_RED, COLOR_BLACK);
}

/**
 * @brief Get the direction from user input into snake 
 * 
 * @param snake 
 */
void get_direction(Snake & snake)    {
    // if no input is given
    int move = ERR;
    int temp;

    // get input as long as we did not read end of input.
    while (ERR != (temp = getch())) {
        move = temp;
    }

    // set the direction accourding to the arrow key, if something else was pressed ignore it.
    switch (move) {
        case KEY_UP:
            snake.set_direction(UP);
            break;
        case KEY_DOWN:
            snake.set_direction(DOWN);
            break;
        case KEY_LEFT:
            snake.set_direction(LEFT);
            break;
        case KEY_RIGHT:
            snake.set_direction(RIGHT);
    }
}

/**
 * @brief update the game variables, snake and food.
 * 
 * @param snake 
 * @param food 
 * @return game is over or not 
 */
bool game_tick(Snake & snake, Food & food)   {
    // move the snake, check if the snake has died
    const bool snake_alive = snake.tick();
    // update the food
    food.tick(snake);

    // print all info to the game
    food.print();
    snake.print();

    // return "is the snake alive?"
    return snake_alive;
}

void game()   {
    // create the game window.
    WINDOW * win = newwin(HEIGHT + 2, WIDTH + 2, 0, 0);
    box(win, '|' , '-');
    // to measure game time.
    const time_t start = time(NULL);
    bool game_running = true;
    
    // create and grow the snake.
    Snake snake(win, (WIDTH + SNAKE_START_SIZE) / 2, HEIGHT / 2, WIDTH, HEIGHT, SNAKE_START_SIZE);

    // create the food.
    Food food(win, {WIDTH, HEIGHT}, snake, FOOD_TIMEOUT);

    while(game_running)    {
        // tick the loop in FPS.
        const tick clock(FPS);

        // get snake movement
        get_direction(snake);

        // tick the game (move the snake update the food...)
        game_running = game_tick(snake, food);

        // print snake size and play time.
        std::stringstream data_msg, time_str;

        // create the stering to print at bottom of the screen
        data_msg << "SIZE: " << snake.size();
        data_msg << std::setw(WIDTH + 2 - data_msg.str().size());
        time_str << "TIME: " << time(NULL) - start << 's';
        data_msg << time_str.str();

        // update screen.
        wrefresh(win);
        mvprintw(HEIGHT + 2, 0 , "%s", data_msg.str().c_str());
    }

    // game over.
    endwin();

    // print game stats.
    std::cout << "SIZE: " << snake.size() << "\tGREW:\t" << snake.size() - SNAKE_START_SIZE << "\t" << "TIME: " << time(NULL) - start << 's' << std::endl;
}

int main()  {
    startup();
    game();
}
