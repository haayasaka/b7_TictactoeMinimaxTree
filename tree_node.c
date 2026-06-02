#include <stdlib.h>
#include <string.h>
#include "tree_node.h"

TreeNode* createNode(char board[], int move, char turn) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    memcpy(node->board, board, BOARD_SIZE);
    node->move       = move;
    node->turn       = turn;
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
