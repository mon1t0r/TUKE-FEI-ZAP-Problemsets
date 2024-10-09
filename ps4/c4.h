#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

/**
 * @brief Initializes the game board.
 *
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param board The 2D array representing the game board.
 */
void initialize_board(int rows, int cols, char board[rows][cols]);

/**
 * @brief Prints the current state of the game board.
 *
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param board The 2D array representing the game board.
 */
void print_board(int rows, int cols, const char board[rows][cols]);

/**
 * @brief Checks if a move is valid.
 *
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param board The 2D array representing the game board.
 * @param col The column where the player wants to make a move.
 * @return 1 if the move is valid, 0 otherwise.
 */
int is_valid_move(int rows, int cols, const char board[rows][cols], int col);

/**
 * @brief Drops a game piece into the specified column.
 *
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param board The 2D array representing the game board.
 * @param col The column where the player wants to make a move.
 * @param player_piece The game piece of the current player.
 * @return The row where the piece was placed or -1 if the column is full.
 */
int drop_piece(int rows, int cols, char board[rows][cols], int col, char player_piece);

/**
 * @brief Checks if the current player has won the game.
 *
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param board The 2D array representing the game board.
 * @param row The row of the last move.
 * @param col The column of the last move.
 * @param player_piece The game piece of the current player.
 * @return 1 if the current player has won, 0 otherwise.
 */
int check_win(int rows, int cols, const char board[rows][cols], int row, int col, char player_piece);

/**
 * @brief Checks if the game board is full.
 *
 * @param rows The number of rows in the board.
 * @param cols The number of columns in the board.
 * @param board The 2D array representing the game board.
 * @return 1 if the board is full, 0 otherwise.
 */
int is_board_full(int rows, int cols, const char board[rows][cols]);

/**
 * Starts interactive c4 game
 */
void run_c4();

#endif // CONNECT_FOUR_H
