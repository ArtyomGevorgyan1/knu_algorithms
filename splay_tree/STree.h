//
// Created by artyom on 25.02.19.
//

#ifndef SPLAY_TREE_STREE_H
#define SPLAY_TREE_STREE_H

#include <fstream>
#include <algorithm>
#include <stack>


struct Node {
    int key;
    Node* left,*right,*parent;
};

class STree {
public:

    STree();

    void insert(Node* i);
    Node* getRoot();
    void setRoot(Node* nr);

private:
    Node* root;
    void rLeft(Node* x);
    void rRight(Node* x);
    void zig(Node* x);
    void zigZig(Node* x);
    void zigZag(Node* x);
    void splay(Node* x);
    Node* merge(Node* x, Node* y);
};

#endif //SPLAY_TREE_STREE_H
