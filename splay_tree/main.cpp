#include <iostream>
#include "STree.h"

#include <vector>
using std::vector;
using std::cin;
using std::cout;

int main() {
    STree t;
    vector <Node*> vec;
    int c;
    cin >> c;
    for (int i = 0; i < c; i++) {
        Node* ne = new Node;
        ne -> key = (i*i);
        ne -> left = nullptr;
        ne -> right = nullptr;
        ne -> parent = nullptr;
        vec.push_back(ne);
    }

    return 0;
}