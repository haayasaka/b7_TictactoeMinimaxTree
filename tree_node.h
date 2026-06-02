#ifndef TREE_NODE_H
#define TREE_NODE_H

#define BOARD_SIZE   9
#define MAX_CHILDREN 9

typedef struct TreeNode {
    char board[BOARD_SIZE];
    int  move;
    char turn;

    struct TreeNode* children[MAX_CHILDREN];
    int              childCount;
} TreeNode;

TreeNode* createNode(char board[], int move, char turn);
void      addChild(TreeNode* parent, TreeNode* child);
int       isLeaf(TreeNode* node);
void      freeNode(TreeNode* node);

#endif // TREE_NODE_H
