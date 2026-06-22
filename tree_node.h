#ifndef TREE_NODE_H
#define TREE_NODE_H

#define BOARD_ROWS   3
#define BOARD_COLS   3
#define MAX_CHILDREN 9

typedef struct TreeNode {
    char board[BOARD_ROWS][BOARD_COLS];
    int  move;
    char turn;
    int  score;

    struct TreeNode* children[MAX_CHILDREN];
    int              childCount;
} TreeNode;

TreeNode* createNode(char board[BOARD_ROWS][BOARD_COLS], int move, char turn);
void      addChild(TreeNode* parent, TreeNode* child);
int       isLeaf(TreeNode* node);
void      freeTree(TreeNode* root);

#endif // TREE_NODE_H
