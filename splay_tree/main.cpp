#include <iostream>
#include "STree.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;

int main() {

    ST t;
    Node* n;
    for (int i = 1; i <= 10; i++) {
        n  = t.getGoodNode(i);
        t.insert(n);
    }
    n  = t.getGoodNode(-1);
    t.insert(n);
    t.show();

    Node* f = t.search(100);


    return 0;
}