#pragma once
#include <iostream>

enum Color { RED, BLACK };

struct RBNode {
    int key;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    RBNode(int k = 0) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL; // sentinel

    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);
    void insertFixup(RBNode* z);
    void transplant(RBNode* u, RBNode* v);
    RBNode* treeMinimum(RBNode* x) const;
    void deleteFixup(RBNode* x);
    void deleteNode(RBNode* z);
    void inorder(RBNode* node) const;
    void destroy(RBNode* node);
    void printLevelOrder() const;

public:
    RedBlackTree();
    ~RedBlackTree();

    void insert(int key);
    bool search(int key) const;
    bool remove(int key);

    void printInorder() const;
    void printTree() const; // level order with colors
};
