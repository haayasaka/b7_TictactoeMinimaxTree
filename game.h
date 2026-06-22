#ifndef GAME_H
#define GAME_H

#include "minimax.h"

void printBoard(char board[BOARD_ROWS][BOARD_COLS]);
void printGrid(void);
int  inputToRow(int pos);
int  inputToCol(int pos);
int  isValidMove(char board[BOARD_ROWS][BOARD_COLS], int pos);
void initBoard(char board[BOARD_ROWS][BOARD_COLS]);

#endif // GAME_H
