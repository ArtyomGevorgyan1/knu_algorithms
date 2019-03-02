//
// Created by artyom on 25.02.19.
//

#ifndef PERSISTENT_RBT_PRBT_H
#define PERSISTENT_RBT_PRBT_H



// 1 red
// 0 black

#include <vector>

struct Node {
    Node* left, *right , *parent;
    int key;
    bool color;

    // size of subtree - need this for order-statistics
    int sz;
};



class PRBT {
public:

    PRBT();

    Node* getRoot();
    void setRoot(Node* r);
    Node* getGoodNode(int v);

    void insert(Node* i);
    void deleteNode(Node* x);

    void show(int ind = -1);

    void leftRotate(Node* x, int ind = -1);
    void rightRotate(Node* x, int ind = -1);
    void transplant(Node* x, Node* y, int ind = -1);



    void pInsert(Node* i);
    void pDelete(Node* i);
    struct List {
        std::vector <Node*> roots;
    } vers;

private:
    void insertFixup(Node* z, int ind = -1);
    void fixDeletion(Node* x, int ind = -1);
    void stackWrite(int ind = -1);

    Node* root;
};



#endif //PERSISTENT_RBT_PRBT_H
