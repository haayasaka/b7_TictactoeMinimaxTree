#ifndef MINIMAX_H
#define MINIMAX_H

#include "tree_node.h"

#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY    '_'

char otherPlayer(char player);
int  isWin(char board[BOARD_ROWS][BOARD_COLS], char player);
int  isBoardFull(char board[BOARD_ROWS][BOARD_COLS]);

TreeNode* buildGameTree(char board[BOARD_ROWS][BOARD_COLS], char turn);
int       minimax(TreeNode* node, char aiPlayer);
int       bestMove(TreeNode* root, char aiPlayer);
int       findBestMove(char board[BOARD_ROWS][BOARD_COLS], char aiPlayer);

#endif // MINIMAX_H
