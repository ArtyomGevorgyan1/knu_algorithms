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

    return 0;
}