#include <iostream>
#include <stack>
#include <fstream>
#include <vector>

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
    RBTree t;

    Node *p = t.getGoodNode(4);
    Node* l = t.getGoodNode(2);
    Node* r = t.getGoodNode(6);
    Node* rl = t.getGoodNode(5);
    Node* rr = t.getGoodNode(7);

    t.insert(p);
    t.insert(l);
    t.insert(r);
    t.insert(rl);
    t.insert(rr);

    t.show();
    t.leftRotate(p);
    t.show();
    return 0;
}