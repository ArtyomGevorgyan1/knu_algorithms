//
// Created by artyom on 17.02.19.
//

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H


// 1 red
// 0 black

struct Node {
    Node* left, *right , *parent;
    int key;
    bool color;
};

class RBTree {
public:

    Node* getRoot();
    void setRoot(Node* r);
    static Node* getGoodNode(int v);

    void insert(Node* i);
    void show();

    void leftRotate(Node* x);
    void rightRotate(Node* x);

private:
    void insertFixup(Node* z);

    void stackWrite();

    static Node* root;
};


#endif //RED_BLACK_TREE_RBTREE_H
