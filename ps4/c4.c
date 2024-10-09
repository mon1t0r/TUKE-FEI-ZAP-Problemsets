#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <curses.h>
#include "c4.h"

#define BLANK '.'
#define PLAYER_1 'X'
#define PLAYER_2 'O'
#define STRIKE 4

int color_for_char(const char c);

void initialize_board(int rows, int cols, char board[rows][cols]) {
    for(int i = 0; i < rows; ++i)
        for(int j = 0; j < cols; ++j)
            board[i][j] = BLANK;
}

void print_board(int rows, int cols, const char board[rows][cols]) {
    attron(COLOR_PAIR(1));
    for(int i = 0; i < rows; ++i) {
        printw("|");
        for(int j = 0; j < cols; ++j) {
            attron(COLOR_PAIR(color_for_char(board[i][j])));
            printw(" %c", board[i][j]);
            attron(COLOR_PAIR(1));
            printw(" |");
        }
        printw("\n");
    }

    attron(COLOR_PAIR(1));
    for(int j = 0; j < cols; ++j)
        printw("+---");
    printw("+\n");

    printw(" ");
    for(int j = 0; j < cols; ++j) {
        attron(COLOR_PAIR(2));
        printw(" %d  ", j + 1);
    }
    printw("\n");
}

int is_valid_move(int rows, int cols, const char board[rows][cols], int col) {
    col--;
    if(col < 0 || col >= cols)
        return 0;
    return board[0][col] == BLANK;
}

int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece) {
    col--;
    if(col < 0 || col >= cols)
        return -1;
    for(int i = rows - 1; i >= 0; --i)
        if(board[i][col] == BLANK) {
            board[i][col] = player_piece;
            return i;
        }
    return -1;
}

int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece) {
    int strike_count = 0;
    for(int i = 0; i < rows; ++i) {
        if(board[i][col] != player_piece)
            break;
        strike_count++;
        if(strike_count >= STRIKE)
            return 1;
    }
    
    strike_count = 0;
    for(int j = 0; j < cols; ++j) {
        if(board[row][j] != player_piece)
            break;
        strike_count++;
        if(strike_count >= STRIKE)
            return 1;
    }

    int start_row = row > col ? row - col : 0;
    int start_col = col > row ? col - row : 0;
    strike_count = 0;
    for(int i = start_row, j = start_col; i < rows && j < cols; ++i, ++j) {
        if(board[i][j] != player_piece)
            break;
        strike_count++;
        if(strike_count >= STRIKE)
            return 1;
    }

    start_row = rows - row - 1 > col ? rows - row - 1 - col : rows - 1;
    start_col = col > rows - row - 1 ? col - rows + row + 1 : 0;
    strike_count = 0;
    for(int i = start_row, j = start_col; i >= 0 && j < cols; --i, ++j) {
        if(board[i][j] != player_piece)
            break;
        strike_count++;
        if(strike_count >= STRIKE)
            return 1;
    }

    return 0;
}

int is_board_full(int rows, int cols, const char board[rows][cols]) {
    for(int j = 0; j < cols; ++j)
        if(board[0][j] == BLANK)
            return 0;
    return 1;
}

void run_c4() {
    const int rows = 4, cols = 5;
    char board[rows][cols];
    initialize_board(rows, cols, board);

    print_board(rows, cols, board);
    refresh();

    int move_col;
    char player = PLAYER_1;
    while(true) {
        attron(COLOR_PAIR(1));
        printw("\nPlayer ");
        attron(COLOR_PAIR(color_for_char(player)));
        printw("%c", player);
        attron(COLOR_PAIR(1));
        printw(", enter your move (1-5): ");
        refresh();

        scanw("%d", &move_col);

        printw("\n");

        if(!is_valid_move(rows, cols, board, move_col)) {
            attron(COLOR_PAIR(3));
            printw("Invalid move!\n");
            print_board(rows, cols, board);
            refresh();
            continue;
        }

        int row = drop_piece(rows, cols, board, move_col, player);

        if(row < 0) {
            attron(COLOR_PAIR(3));
            printw("Failed to move!\n");
            print_board(rows, cols, board);
            refresh();
            continue;
        }

        print_board(rows, cols, board);
        refresh();

        if(check_win(rows, cols, board, row, move_col - 1, player)) {
            attron(COLOR_PAIR(1));
            printw("Player ");
            attron(COLOR_PAIR(color_for_char(player)));
            printw("%c", player);
            attron(COLOR_PAIR(1));
            printw(" wins!\n");
            break;
        }

        if(is_board_full(rows, cols, board)) {
            attron(COLOR_PAIR(1));
            printw("Draw!\n");
            break;
        }

        player = player == PLAYER_1 ? PLAYER_2 : PLAYER_1;
    }
    
    printw("Press any key to exit . . .");
    refresh();
    getch();
}


int color_for_char(const char c) {
    switch (c)
    {
    case PLAYER_1:
        return 3;
    case PLAYER_2:
        return 5;
    }
    return 1;
}