#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include "ballsortpuzzle.h"

#define SYMBOLS_ORIGIN '#'
#define EMPTY_COLUMNS 2
#define PALETTE_ORIGIN 3
#define PALETTE_COUNT 7

int rand_index(const int avaliable_size, const bool avaliable[avaliable_size], const int excluded_count);
int rand_range(const int min, const int max);

void generator(const int rows, const int columns, char field[rows][columns]) {
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < columns; ++j)
            field[i][j] = BLANK;

    int symbols_size = (columns - EMPTY_COLUMNS) * rows;
    bool symbols_avaliable[symbols_size];
    for(int i = 0; i < symbols_size; ++i)
        symbols_avaliable[i] = true;
    
    int symbols_excluded_count = 0;

    int empty_cols[EMPTY_COLUMNS];
    empty_cols[0] = rand_range(0, columns);
    int r1 = rand_range(0, columns - 1);
    empty_cols[1] = r1 < empty_cols[0] ? r1 : r1 + 1;

    for(int j = 0; j < columns; ++j) {
        if(j == empty_cols[0] || j == empty_cols[1])
            continue;
        
        for(int i = 0; i < rows; ++i) {
            int index = rand_index(symbols_size, symbols_avaliable, symbols_excluded_count);
            symbols_avaliable[index] = false;
            symbols_excluded_count++;

            field[i][j] = SYMBOLS_ORIGIN + index / rows;
        }
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y) {
    x--;
    y--;
    
    if(x < 0 || y < 0 || x > columns || y > columns) {
        attron(COLOR_PAIR(3));
        printw("Out of bounds!\n");
        return;
    }

    if(x == y) {
        attron(COLOR_PAIR(3));
        printw("Origin can not be equal to destination!\n");
        return;
    }
    
    int start_row_index = -1;
    for(int i = 0; i < rows; ++i) {
        if(field[i][x] != BLANK) {
            start_row_index = i;
            break;
        }
    }

    if(start_row_index < 0) {
        attron(COLOR_PAIR(3));
        printw("Origin column is empty!\n");
        return;
    }

    int end_row_index = rows - 1;
    for(int i = 1; i < rows; ++i) {
        if(field[i][y] != BLANK) {
            end_row_index = i - 1;
            break;
        }
    }

    if(field[end_row_index][y] != BLANK) {
        attron(COLOR_PAIR(3));
        printw("Destination column is full!\n");
        return;
    }

    if(end_row_index < rows - 1 && field[start_row_index][x] != field[end_row_index + 1][y]) {
        attron(COLOR_PAIR(3));
        printw("Destination color must be equal to origin!\n");
        return;
    }
    
    field[end_row_index][y] = field[start_row_index][x];
    field[start_row_index][x] = BLANK;
}

bool check(const int rows, const int columns, char field[rows][columns]) {
    char symbol;
    int empty_cols = 0;

    for(int j = 0; j < columns; ++j) {
        if(field[0][j] == BLANK) {
            empty_cols++;
            if(empty_cols > EMPTY_COLUMNS)
                return false;
            continue;
        }

        symbol = field[0][j];
        for(int i = 1; i < rows; ++i) {
            if(field[i][j] != symbol)
                return false;
        }
    }

    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns]) {
    for(int i = 0; i < rows; ++i) {
        attron(COLOR_PAIR(2));
        printw(" %d", i + 1);
        attron(COLOR_PAIR(1));
        printw(" |");

        for(int j = 0; j < columns; ++j) {
            int col = field[i][j] - SYMBOLS_ORIGIN;
            while(col >= PALETTE_COUNT)
                col -= PALETTE_COUNT;
            
            attron(COLOR_PAIR(PALETTE_ORIGIN + col));
            printw(" %c", field[i][j]);
            attron(COLOR_PAIR(1));
            printw(" |");
        }
        printw("\n");
    }

    attron(COLOR_PAIR(1));
    printw("   ");
    for(int j = 0; j < columns; ++j)
        printw("+---");
    printw("+\n");

    attron(COLOR_PAIR(2));
    printw("   ");
    for(int j = 0; j < columns; ++j)
        printw("  %d ", j + 1);
    printw("\n");
}

void ball_sort_puzzle() {
    const int rows = 4, columns = 6;
    char field[rows][columns];
    generator(rows, columns, field);
    game_field(rows, columns, field);
    refresh();

    int origin, destination;
    while(!check(rows, columns, field)) {
        attron(COLOR_PAIR(5));
        printw("Enter origin: ");
        refresh();
        attron(COLOR_PAIR(1));
        scanw("%d", &origin);
        
        attron(COLOR_PAIR(6));
        printw("Enter destination: ");
        refresh();
        attron(COLOR_PAIR(1));
        scanw("%d", &destination);

        down_possible(rows, columns, field, origin, destination);
        printw("\n");
        game_field(rows, columns, field);
        refresh();
    }

    attron(COLOR_PAIR(1));
    printw("\nYou won! Congratulations!\nPress any key to exit . . .");
    refresh();
    getch();
}


int rand_index(const int avaliable_size, const bool avaliable[avaliable_size], const int excluded_count) {
    int random = rand_range(0, avaliable_size - excluded_count);

    int index = 0;
    for(int i = 0; i < avaliable_size; ++i) {
        if(!avaliable[i])
            continue;
        if(++index >= random)
            return i;
    }

    return 0;
}

int rand_range(const int min, const int max) {
    return min + rand() % (max - min);
}