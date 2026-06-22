#include <stdio.h>
#include "game.h"

int main() {
    char board[BOARD_ROWS][BOARD_COLS];
    int  pos;

    initBoard(board);

    printf("\n=== TIC-TAC-TOE: Manusia (X) vs Komputer (O) ===\n");
    printf("Anda tempatkan X, komputer akan membalas dengan O.\n");
    printGrid();
    printBoard(board);

    // Input user (X)
    do {
        printf("Giliran Anda (X). Masukkan posisi (1-9): ");
        if (scanf("%d", &pos) != 1) {
            while (getchar() != '\n');
            pos = -1;
        }
        if (!isValidMove(board, pos))
            printf("Posisi tidak valid atau sudah terisi. Coba lagi.\n");
    } while (!isValidMove(board, pos));

    board[inputToRow(pos)][inputToCol(pos)] = PLAYER_X;

    // Cek apakah user langsung menang setelah satu langkah (biasanya tidak)
    if (isWin(board, PLAYER_X)) {
        printBoard(board);
        printf("Anda menang dalam satu langkah!\n");
        return 0;
    }

    // AI balas dengan O
    printf("\n--- Giliran Komputer (O) ---\n");
    int best = findBestMove(board, PLAYER_O);
    if (best >= 0) {
        int r = best / BOARD_COLS;
        int c = best % BOARD_COLS;
        board[r][c] = PLAYER_O;
        printf("Komputer memilih posisi %d.\n", best + 1);
        printBoard(board);

        if (isWin(board, PLAYER_O))
            printf("Komputer menang!\n");
        else if (isBoardFull(board))
            printf("Papan penuh (seri).\n");
    }

    return 0;
}
