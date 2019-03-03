#include <iostream>
#include <vector>
using std::vector;

#include "PRBT.h"
int main() {
    PRBT t;

    Node* f;
    vector <Node*> vec;
    for (int i = 1; i < 10; i++) {
        f = t.getGoodNode(i);
        vec.push_back(f);
    }

    for (auto i : vec)
        t.pInsert(i);

    for (auto i: vec) {
        t.pDelete(i);
    }

    t.pInsert(t.getGoodNode(5));

    t.show(13);

    return 0;
}

/*
 *
 * TODO:
 * - show a tree instead of a graph wuth graphviz (attributes like left, right chil and parent)
 *
 */