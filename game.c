#include <stdio.h>
#include "game.h"

void printBoard(char board[BOARD_ROWS][BOARD_COLS]) {
    printf("\n");
    for (int r = 0; r < BOARD_ROWS; r++) {
        printf(" ");
        for (int c = 0; c < BOARD_COLS; c++) {
            printf("%c", board[r][c]);
            if (c < BOARD_COLS - 1) printf(" | ");
        }
        printf("\n");
        if (r < BOARD_ROWS - 1) printf("---|---|---\n");
    }
    printf("\n");
}

void printGrid(void) {
    printf("\nPetunjuk posisi (masukkan angka 1-9):\n");
    printf(" 1 | 2 | 3\n");
    printf("---|---|---\n");
    printf(" 4 | 5 | 6\n");
    printf("---|---|---\n");
    printf(" 7 | 8 | 9\n");
    printf("\n");
}

int inputToRow(int pos) { return (pos - 1) / BOARD_COLS; }
int inputToCol(int pos) { return (pos - 1) % BOARD_COLS; }

int isValidMove(char board[BOARD_ROWS][BOARD_COLS], int pos) {
    if (pos < 1 || pos > 9) return 0;
    int r = inputToRow(pos);
    int c = inputToCol(pos);
    return board[r][c] == EMPTY;
}

void initBoard(char board[BOARD_ROWS][BOARD_COLS]) {
    for (int r = 0; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS; c++)
            board[r][c] = EMPTY;
}
