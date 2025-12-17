#include "RedBlack.hpp"
#include <queue>

RedBlackTree::RedBlackTree() {
    NIL = new RBNode();
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
    root = NIL;
}

RedBlackTree::~RedBlackTree() {
    destroy(root);
    delete NIL;
}

void RedBlackTree::destroy(RBNode* node) {
    if (node == NIL) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void RedBlackTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NIL) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insert(int key) {
    RBNode* z = new RBNode(key);
    z->left = z->right = z->parent = NIL;

    RBNode* y = NIL;
    RBNode* x = root;
    while (x != NIL) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }
    z->parent = y;
    if (y == NIL) root = z;
    else if (z->key < y->key) y->left = z;
    else y->right = z;

    z->left = z->right = NIL;
    z->color = RED;
    insertFixup(z);
}

void RedBlackTree::insertFixup(RBNode* z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
        if (z == root) break;
    }
    root->color = BLACK;
}

bool RedBlackTree::search(int key) const {
    RBNode* cur = root;
    while (cur != NIL) {
        if (key == cur->key) return true;
        if (key < cur->key) cur = cur->left;
        else cur = cur->right;
    }
    return false;
}

RBNode* RedBlackTree::treeMinimum(RBNode* x) const {
    while (x->left != NIL) x = x->left;
    return x;
}

void RedBlackTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == NIL) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
}

bool RedBlackTree::remove(int key) {
    RBNode* z = root;
    while (z != NIL && z->key != key) {
        if (key < z->key) z = z->left;
        else z = z->right;
    }
    if (z == NIL) return false;
    deleteNode(z);
    return true;
}

void RedBlackTree::deleteNode(RBNode* z) {
    RBNode* y = z;
    Color yOriginalColor = y->color;
    RBNode* x;
    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = treeMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK) deleteFixup(x);
}

void RedBlackTree::deleteFixup(RBNode* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            RBNode* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void RedBlackTree::inorder(RBNode* node) const {
    if (node == NIL) return;
    inorder(node->left);
    std::cout << node->key << (node->color==RED?"(R)":"(B)") << " ";
    inorder(node->right);
}

void RedBlackTree::printInorder() const {
    inorder(root);
    std::cout << "\n";
}

void RedBlackTree::printLevelOrder() const {
    if (root == NIL) { std::cout << "<empty>\n"; return; }
    std::queue<RBNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; ++i) {
            RBNode* n = q.front(); q.pop();
            std::cout << n->key << (n->color==RED?"(R)":"(B)") << " ";
            if (n->left != NIL) q.push(n->left);
            if (n->right != NIL) q.push(n->right);
        }
        std::cout << "\n";
    }
}

void RedBlackTree::printTree() const {
    std::cout << "Inorder (key(color)): ";
    printInorder();
    std::cout << "Level order:\n";
    printLevelOrder();
}
