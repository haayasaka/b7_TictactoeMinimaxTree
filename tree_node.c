#include <stdlib.h>
#include <string.h>
#include "tree_node.h"

TreeNode* createNode(char board[BOARD_ROWS][BOARD_COLS], int move, char turn) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    memcpy(node->board, board, sizeof(node->board));
    node->move       = move;
    node->turn       = turn;
    node->score      = 0; // Default score
    node->childCount = 0;
    for (int i = 0; i < MAX_CHILDREN; i++) node->children[i] = NULL;
    return node;
}

void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->childCount < MAX_CHILDREN)
        parent->children[parent->childCount++] = child;
}

int isLeaf(TreeNode* node) {
    return node->childCount == 0;
}

void freeNode(TreeNode* node) {
    if (node != NULL) free(node);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < root->childCount; i++) {
        freeTree(root->children[i]);
    }
    free(root);
}
