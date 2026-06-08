#include <string.h>
#include <limits.h>
#include "minimax.h"

char otherPlayer(char player) {
    return (player == PLAYER_X) ? PLAYER_O : PLAYER_X;
}

int isWin(char board[BOARD_ROWS][BOARD_COLS], char player) {
    // Cek tiga baris dan tiga kolom
    for (int i = 0; i < BOARD_ROWS; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    // Cek dua diagonal
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return 1;

    return 0;
}

int isBoardFull(char board[BOARD_ROWS][BOARD_COLS]) {
    for (int r = 0; r < BOARD_ROWS; r++)
        for (int c = 0; c < BOARD_COLS; c++)
            if (board[r][c] == EMPTY)
                return 0; // masih ada sel kosong
    return 1;
}

// Bangun subpohon dari papan tertentu. move adalah langkah yang menghasilkan
// papan ini (root memakai -1), turn pemain yang akan melangkah selanjutnya.
static TreeNode* buildSubtree(char board[BOARD_ROWS][BOARD_COLS], int move, char turn) {
    TreeNode* node = createNode(board, move, turn);

    // Kalau papan sudah terminal (ada yang menang atau penuh), berhenti di sini.
    if (isWin(board, PLAYER_X) || isWin(board, PLAYER_O) || isBoardFull(board))
        return node;

    // Coba setiap sel kosong sebagai langkah berikutnya bagi pemain turn.
    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        int r = i / BOARD_COLS;
        int c = i % BOARD_COLS;
        if (board[r][c] == EMPTY) {
            char next[BOARD_ROWS][BOARD_COLS];
            memcpy(next, board, sizeof(next));
            next[r][c] = turn; // pemain turn mengisi sel ini

            TreeNode* child = buildSubtree(next, i, otherPlayer(turn));
            addChild(node, child);
        }
    }

    return node;
}

TreeNode* buildGameTree(char board[BOARD_ROWS][BOARD_COLS], char turn) {
    return buildSubtree(board, -1, turn);
}

// Inti rekursif minimax. depth adalah jarak langkah dari root, dipakai supaya
// AI memilih kemenangan tercepat dan menunda kekalahan selama mungkin.
static int minimaxRec(TreeNode* node, char aiPlayer, int depth) {
    char human = otherPlayer(aiPlayer);

    // Evaluasi kondisi terminal dari sudut pandang AI.
    if (isWin(node->board, aiPlayer)) {
        node->score = 10 - depth;
        return node->score;
    }
    if (isWin(node->board, human)) {
        node->score = depth - 10;
        return node->score;
    }
    if (isLeaf(node)) {
        // Tidak ada yang menang dan tidak punya anak, berarti papan penuh: seri.
        node->score = 0;
        return node->score;
    }

    if (node->turn == aiPlayer) {
        // Giliran AI: ambil langkah dengan skor tertinggi (maximizing).
        int best = INT_MIN;
        for (int i = 0; i < node->childCount; i++) {
            int val = minimaxRec(node->children[i], aiPlayer, depth + 1);
            if (val > best) best = val;
        }
        node->score = best;
    } else {
        // Giliran lawan: dianggap memilih skor terendah bagi AI (minimizing).
        int best = INT_MAX;
        for (int i = 0; i < node->childCount; i++) {
            int val = minimaxRec(node->children[i], aiPlayer, depth + 1);
            if (val < best) best = val;
        }
        node->score = best;
    }

    return node->score;
}

int minimax(TreeNode* node, char aiPlayer) {
    if (node == NULL) return 0;
    return minimaxRec(node, aiPlayer, 0);
}

int bestMove(TreeNode* root, char aiPlayer) {
    if (root == NULL || isLeaf(root))
        return -1; // tidak ada langkah yang bisa diambil

    minimax(root, aiPlayer); // isi score seluruh node lebih dulu

    int chosen = -1;

    if (root->turn == aiPlayer) {
        // Pilih anak dengan skor tertinggi (langkah terbaik untuk AI).
        int best = INT_MIN;
        for (int i = 0; i < root->childCount; i++) {
            if (root->children[i]->score > best) {
                best   = root->children[i]->score;
                chosen = root->children[i]->move;
            }
        }
    } else {
        // Kalau ternyata giliran lawan, ambil anak dengan skor terendah.
        int best = INT_MAX;
        for (int i = 0; i < root->childCount; i++) {
            if (root->children[i]->score < best) {
                best   = root->children[i]->score;
                chosen = root->children[i]->move;
            }
        }
    }

    return chosen;
}

int findBestMove(char board[BOARD_ROWS][BOARD_COLS], char aiPlayer) {
    TreeNode* root = buildGameTree(board, aiPlayer);
    int move = bestMove(root, aiPlayer);
    freeTree(root);
    return move;
}
