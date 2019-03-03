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
    Node* left, *right, *parent;
};

class ST {
public:
    ST();
    ~ST();

    void insert(Node* i);
    Node* getGoodNode(int k);
    void splay(Node* x);
    void lRotate(Node* x);
    void rRotate(Node* x);
    Node* search(int k);
    Node* _search(int k, Node* r);
    Node* maxElem(Node* x);
    Node* minElem(Node* x);
    Node* join(Node* l, Node* r);
    std::pair <Node*, Node*> split(Node* t, int key);
    void remove(int key);

    void show();
    void stackWrite();

private:
    Node* root;
};


#endif //SPLAY_TREE_STREE_H
