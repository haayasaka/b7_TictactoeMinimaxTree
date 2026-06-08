#ifndef MINIMAX_H
#define MINIMAX_H

#include "tree_node.h"

// Karakter pemain dan sel kosong pada papan
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY    '_'

// Kembalikan lawan dari player (X jadi O, O jadi X)
char otherPlayer(char player);

// Cek apakah player sudah menang (ada satu baris/kolom/diagonal penuh)
int isWin(char board[BOARD_ROWS][BOARD_COLS], char player);

// Cek apakah papan sudah penuh (tidak ada sel kosong lagi)
int isBoardFull(char board[BOARD_ROWS][BOARD_COLS]);

// Bangun seluruh pohon kemungkinan permainan dari papan dan giliran sekarang.
// turn adalah pemain yang akan melangkah dari papan tersebut.
// Node root punya move = -1. Kembalikan pointer ke root.
TreeNode* buildGameTree(char board[BOARD_ROWS][BOARD_COLS], char turn);

// Telusuri pohon secara rekursif, isi field score tiap node memakai algoritma
// minimax (depth-weighted) dari sudut pandang aiPlayer, lalu kembalikan score node.
int minimax(TreeNode* node, char aiPlayer);

// Jalankan minimax pada pohon lalu kembalikan indeks langkah terbaik (0..8)
// untuk aiPlayer. Kembalikan -1 kalau tidak ada langkah yang bisa diambil.
int bestMove(TreeNode* root, char aiPlayer);

// Versi satu panggilan: bangun pohon dari papan, cari langkah terbaik untuk
// aiPlayer, bebaskan memori pohon, lalu kembalikan indeks langkahnya (0..8).
int findBestMove(char board[BOARD_ROWS][BOARD_COLS], char aiPlayer);

#endif // MINIMAX_H
