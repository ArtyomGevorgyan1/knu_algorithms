#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <set>

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

    std::set <int> s;

    for (int i = 0; i < 50; i++) {
        t.insert(t.getGoodNode((i*i)%10000001));
    }
    t.show();

    return 0;
}