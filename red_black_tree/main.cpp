#include <iostream>
#include <stack>
#include <fstream>

using std::stack;
using std::ofstream;
using std::cout;

#include "RBTree.h"

void deb(Node* f) {
    if (f) {
        if (f -> left) {
            deb(f -> left);
        }
        cout << f -> key << " ";
        if (f -> right) {
            deb(f -> right);
        }
    }
}

int main() {


    /*
    RBTree tree;
    Node* p = tree.getGoodNode(4);
    Node* l = tree.getGoodNode(1);
    Node* r = tree.getGoodNode(7);
    Node* rr = tree.getGoodNode(10);
    //p -> left = l;
    //p -> right = r;
    //l -> parent = r -> parent = p;
    //rr -> parent = r;
    //r -> right = rr;
    Node* rl = tree.getGoodNode(6);
    //rl -> parent = r;
    //r -> left = rl;
    //tree.setRoot(p);
    //tree.leftRotate(p);
    //tree.rightRotate(r);
    tree.insert(p);
    tree.insert(rr);
    tree.insert(l);
    tree.insert(r);
    tree.insert(rl);
    tree.show();

    //deb(tree.getRoot());
     */

    RBTree tree;
    for (int i = 0; i < 13; i++ ){
        Node* node  = tree.getGoodNode(i % 10);
        tree.insert(node);
    }
    tree.show();

    return 0;
}