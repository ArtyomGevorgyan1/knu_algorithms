#include <iostream>
#include <stack>
#include <fstream>
#include <vector>
#include <set>

using std::stack;
using std::ofstream;
using std::cout;

#include "RBTree.h"

int main() {
    RBTree t;

    std::set <int> s;

    Node* f;
    std::vector <Node*> vec;

    for (int i = 0; i < 50; i++) {

        f = t.getGoodNode(i * i);
        if (i * i == 361) {
            vec.push_back(f);
        }
        t.insert(f);
    }



    //t.deleteNode(vec[0]);
    t.show();

    return 0;
}