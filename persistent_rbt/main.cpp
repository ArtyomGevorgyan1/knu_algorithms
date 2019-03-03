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


    return 0;
}