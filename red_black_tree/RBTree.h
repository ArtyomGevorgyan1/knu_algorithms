//
// Created by artyom on 17.02.19.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

struct Node {
    Node* left, *right;
    int key;
};

class RBTree {
public:

    Node* getRoot();
    void show();
    void setRoot(Node* r);

private:
    void walk(Node* root, int d = 0);
    Node* root;
};


#endif //RED_BLACK_TREE_RBTREE_H
