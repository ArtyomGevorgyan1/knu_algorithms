//
// Created by artyom on 17.02.19.
//

#include "RBTree.h"
#include <iostream>
using namespace std;

Node *RBTree::getRoot() {
    return root;
}

void RBTree::show() {
    walk(root);
}

void RBTree::walk(Node* root, int d) {
    if (root == nullptr) {
        return;
    }
    if (root -> left) {
        walk(root -> left, d+1);
    }

    cout << root-> key;

    if (root -> right) {
        walk(root -> right, d+1);
    }
}

void RBTree::setRoot(Node *r) {
    root = r;
}

