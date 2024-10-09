#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include "ballsortpuzzle.h"
#include "c4.h"

int main()
{
    initscr();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_CYAN, COLOR_BLACK);

    scrollok(stdscr, TRUE);

    srand(time(NULL));

    // The second game will be run right after the first ends
    ball_sort_puzzle();
    run_c4();

    endwin();
}