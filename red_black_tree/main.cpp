#include <iostream>

#include "RBTree.h"

int main() {

    RBTree t;


    Node l;
    l.key = 1;

    Node r;
    r.key = 2;

    Node p;
    p.key = 3;

    p.left = &l;
    p.right = &r;

    l.right = l.left = nullptr;
    r.left = r.right = nullptr;

    t.setRoot(&p);
    t.show();

    return 0;
}