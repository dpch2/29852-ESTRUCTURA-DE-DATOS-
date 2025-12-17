#pragma once
#include <iostream>
#include <queue>

enum Color { RED, BLACK };

struct RBNode {
    int key;
    Color color;
    RBNode *left, *right, *parent;
    RBNode(int k = 0): key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int key);
    bool remove(int key);
    RBNode* search(int key) const;
    void printTree() const; // level-order with colors

private:
    RBNode* root;
    RBNode* NIL; // sentinel

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* y);
    void insertFixup(RBNode* z);
    void transplant(RBNode* u, RBNode* v);
    RBNode* minimum(RBNode* x) const;
    void deleteFixup(RBNode* x);
    void destroy(RBNode* node);
};
