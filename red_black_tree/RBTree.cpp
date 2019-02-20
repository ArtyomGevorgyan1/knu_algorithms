//
// Created by artyom on 17.02.19.
//

#include "RBTree.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

RBTree::RBTree() {
    root = new Node;
    root = nullptr;
}

Node *RBTree::getRoot() {
    return root;
}

void RBTree::show() {
    stackWrite();
    system("./show_png.sh");
}

void RBTree::stackWrite() {
    ofstream dotFile;
    dotFile.open ("./gr.dot");
    dotFile << "digraph {\n";
    //dotFile << "\t" << "a" << " [fillcolor=red style=filled];";

    stack <Node*> st;
    Node* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur -> left;
        }
        cur = st.top();
        st.pop();
        if (cur -> color == 1)
            dotFile << "\t" << cur -> key << " [fillcolor=red style=filled];\n";
        else if (cur -> color == 0)
            dotFile << "\t" << cur -> key << ";\n";
        if (cur -> left) {
            dotFile << "\t" << cur -> key << " -> " << cur -> left -> key << ";\n";

            if (cur -> left -> color == 1)
                dotFile << "\t" << cur -> left -> key << " [fillcolor=red style=filled];\n";
        }
        if (cur -> right) {
            dotFile << "\t" << cur -> key << " -> " << cur -> right -> key << ";\n";

            if (cur -> right -> color == 1)
                dotFile << "\t" << cur -> right -> key << " [ fillcolor = red style=filled];\n";
        }
        cur = cur -> right;
    }

    dotFile << "}\n";
    dotFile.close();
}



void RBTree::insert(Node *i) {

    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;
        if (i->key < x -> key) {
            x = x -> left;
        } else  {
            x = x -> right;
        }
    }

    i -> parent = y;
    if (y == nullptr) {
        root = i;
    }
    else if (i -> key < y -> key) {
        y -> left = i;
    } else {
        y -> right = i;
    }
    insertFixup(i);

}

void RBTree::setRoot(Node *r) {
    root = r;
}

Node *RBTree::getGoodNode(int v) {
    auto goodN = new Node;
    goodN->left = nullptr;
    goodN -> right = nullptr;
    goodN ->parent = nullptr;
    goodN -> key = v;
    goodN -> color = true;
    return goodN;
}

void RBTree::insertFixup(Node *z) {
    while (z -> parent && z -> parent -> color == 1) {
        if (z -> parent == z -> parent ->parent -> left) {
            Node* y = z -> parent -> parent -> right;
            if (y && y -> color == 1) {
                z -> parent -> color = 0;
                y -> color = 0;
                z -> parent -> parent -> color = 1;
                z = z -> parent -> parent;
            } else {
                if (z -> parent -> right == z) {
                    z = z -> parent;
                    leftRotate(z);
                }
                z -> parent -> color = 0;
                z -> parent -> parent -> color = 1;
                rightRotate(z -> parent -> parent);

            }
        } else if (z -> parent == z -> parent -> parent -> right) {
            Node* y = z -> parent -> parent -> left;
            if (y && y -> color == 1) {
                z -> parent -> color = 0;
                y -> color = 0;
                z -> parent -> parent -> color = 1;
                z = z -> parent -> parent;
            } else {
                if (z -> parent -> left == z) {
                    z = z -> parent;
                    rightRotate(z);
                }
                z -> parent -> color = 0;
                z -> parent -> parent -> color = 1;
                leftRotate(z -> parent -> parent);
            }
        }
    }
    if (root) {
        root -> color = 0;
    }
}

void RBTree::leftRotate(Node *x) {
    if (!x) return;

    Node* y = nullptr;
    if (x -> right) y = x -> right;

    if (y) {
        if (y -> left) {
            y -> left -> parent = x;
            x -> right = y -> left;
        } else {
            x -> right = nullptr;
        }

        if (x -> parent) {
            y -> parent = x -> parent;

            if (x -> parent -> left == x) {
                x -> parent -> left = y;
            } else if (x -> parent -> right == x) {
                x -> parent -> right = y;
            }
        } else {
            // cout << "haha\n";
        }

        x -> parent = y;
        y -> left = x;

        if (x == root) {
            root = y;
        }
    } else {
        return;
    }
}

void RBTree::rightRotate(Node *x) {
    if (!x) return;

    Node* y = nullptr;
    if (x -> left) y = x -> left;

    if (y) {
        if (y -> right) {
            y -> right -> parent = x;
            x -> left = y -> right;
        } else {
            x -> left = nullptr;
        }

        if (x -> parent) {
            y -> parent = x -> parent;

            if (x -> parent -> left == x) {
                x -> parent -> left = y;
            } else if (x -> parent -> right == x) {
                x -> parent -> right = y;
            }
        } else {
            // cout << "haha\n";
        }

        x -> parent = y;
        y -> right = x;

        if (x == root) {
            root = y;
        }
    } else {
        return;
    }
}
