//
// Created by artyom on 25.02.19.
//

#include "STree.h"

void STree::setRoot(Node* nr) {
    root = nr;
}

Node *STree::getRoot() {
    return root;
}

void STree::insert(Node *i) {
    if (!root) {
        root = i;
        return;
    }
    Node* cur = root;
    while (cur) {



        if (cur -> key > i -> key) {
            if (cur -> left) {
                cur = cur -> left;
            } else {
                cur -> left = i;
                i -> parent = cur;
                return;
            }
        } else {
            if (cur -> right) {
                cur = cur -> right;
            } else {
                cur -> right = i;
                i -> parent = cur;
                return;
            }
        }
    }
}

STree::STree() : root(nullptr)
{

}

void STree::rLeft(Node* x) {
    if (!x) {
        return;
    }

    Node* y = x -> parent;
    if (x -> parent) {
        if (x -> left) {
            x -> parent -> right = x -> left;
            x -> left -> parent = x -> parent;
        } else {
            x -> parent -> right = nullptr;
        }

        if (x -> parent -> parent) {
            if (x -> parent == x -> parent -> parent -> left) {
                x -> parent -> parent -> left = x;
                x -> parent = x -> parent -> parent;
            } else {
                x -> parent -> parent -> right = x;
                x -> parent = x -> parent -> parent;
            }
        } else {
            root = x;
        }
    } else {
        return;
    }

    //Node* y = x -> parent;
    x -> left = y;
    y -> parent = x;

}


void STree::rRight(Node* x) {
    if (!x) {
        return;
    }

    Node* y = x -> parent;
    if (x -> parent) {
        if (x -> right) {
            x -> parent -> left = x -> right;
            x -> right -> parent = x -> parent;
        } else {
            x -> parent -> left = nullptr;
        }

        if (x -> parent -> parent) {
            if (x -> parent == x -> parent -> parent -> left) {
                x -> parent -> parent -> left = x;
                x -> parent = x -> parent -> parent;
            } else {
                x -> parent -> parent -> right = x;
                x -> parent = x -> parent -> parent;
            }
        } else {
            root = x;
        }
    } else {
        return;
    }

    x -> right = y;
    y -> parent = x;
}

void STree::zig(Node *x) {
    if (x -> parent && x -> parent == root) {
        if (x == x -> parent -> left) {
            rRight(x);
        } else {
            rLeft(x);
        }
    } else {
        return;
    }
}

void STree::zigZig(Node *x) {
    if (x -> parent && x -> parent -> parent) {
        if (x == x -> parent -> left && x -> parent == x -> parent -> parent -> left) {
            rRight(x -> parent);
            rRight(x);
        } else if (x == x -> parent -> right && x -> parent == x -> parent -> parent -> right) {
            rLeft(x -> parent);
            rLeft(x);
        }
    } else return;
}

void STree::zigZag(Node *x) {
    if (x -> parent && x -> parent -> parent) {
        if (x == x -> parent -> left && x -> parent == x -> parent -> parent -> right) {
            rRight(x);
            rLeft(x);
        } else if (x == x -> parent -> right && x -> parent == x -> parent -> parent -> left) {
            rLeft(x);
            rRight(x);
        }
    } else return;
}

void STree::splay(Node *x) {
    if (x -> parent && x -> parent == root) {
        zig(x);
    } else if (x -> parent && x -> parent -> parent) {
        if ((x == x -> parent -> left && x -> parent == x -> parent -> parent -> left) ||
            (x == x -> parent -> right && x -> parent == x -> parent -> parent -> right))
        {
            zigZig(x);
        }
        else if ((x == x -> parent -> left && x -> parent == x -> parent -> parent -> right) ||
                (x == x -> parent -> right && x -> parent == x -> parent -> parent -> left))
        {
            zigZag(x);
        }
    }
}

Node* STree::merge(Node *x, Node* y) {
    Node* cur = x;
    while (cur -> right) {
        cur = cur -> right;
    }

    splay(cur);
    cur -> right = y;
    return cur;
}


