//
// Created by artyom on 25.02.19.
//

#include "PRBT.h"

//
// Created by artyom on 17.02.19.
//

#include "PRBT.h"
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

PRBT::PRBT() {
    root = new Node;
    root = nullptr;
}

Node *PRBT::getRoot() {
    return root;
}

void PRBT::show(int ind) {
    stackWrite(ind);
    system("./show_png.sh");
}

void PRBT::stackWrite(int ind) {
    ofstream dotFile;
    dotFile.open ("./gr.dot");
    dotFile << "digraph {\n";
    //dotFile << "\t" << "a" << " [fillcolor=red style=filled];";

    stack <Node*> st;

    Node* cur;
    if (ind == -1)
        cur = root;
    else
        cur = vers.roots[ind];

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



void PRBT::insert(Node *i) {

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

void PRBT::setRoot(Node *r) {
    root = r;
}

Node *PRBT::getGoodNode(int v) {
    auto goodN = new Node;
    goodN->left = nullptr;
    goodN -> right = nullptr;
    goodN ->parent = nullptr;
    goodN -> key = v;
    goodN -> color = true;



    return goodN;
}

void PRBT::insertFixup(Node *z, int ind) {

    while (z -> parent && z -> parent -> color == 1) {
        if (z -> parent == z -> parent ->parent -> left) {
            Node* y = z -> parent -> parent -> right;
            if (y && y -> color == 1) {
                z -> parent -> color = false;
                y -> color = false;
                z -> parent -> parent -> color = true;
                z = z -> parent -> parent;
            } else {
                if (z -> parent -> right == z) {
                    z = z -> parent;
                    leftRotate(z, ind);
                }
                z -> parent -> color = false;
                z -> parent -> parent -> color = true;
                rightRotate(z -> parent -> parent, ind);

            }
        } else if (z -> parent == z -> parent -> parent -> right) {

            Node* y = z -> parent -> parent -> left;
            if (y && y -> color == 1) {
                z -> parent -> color = false;
                y -> color = false;
                z -> parent -> parent -> color = true;
                z = z -> parent -> parent;
            } else {
                if (z -> parent -> left == z) {
                    z = z -> parent;
                    rightRotate(z, ind);
                }
                z -> parent -> color = false;
                z -> parent -> parent -> color = true;
                leftRotate(z -> parent -> parent, ind);
            }
        }
    }



    if (ind == -1 && root) {
        root -> color = false;
    } else {
        vers.roots[ind] -> color = false;
    }



}

void PRBT::leftRotate(Node *x, int ind) {


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

        if (ind == -1 && x == root) {
            root = y;
        } else {
            if (ind != -1 && vers.roots[ind] == x) {
                vers.roots[ind] = y;
            }
        }

        int stop = 5;
        int fsdfsdf = stop;

    } else {
        return;
    }
}

void PRBT::rightRotate(Node *x, int ind) {
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

        if (ind == -1 && x == root) {
            root = y;
        } else {
            if (ind != -1 && vers.roots[ind] == x) {
                vers.roots[ind] = y;
            }
        }
    } else {
        return;
    }
}

void PRBT::transplant(Node *x, Node *y, int ind) {

    if (ind != -1) {
        if (!x) return;
        if (vers.roots[ind] == x) {
            x -> parent = nullptr;
        }

        if (x -> parent == nullptr) {
            vers.roots[ind] = y;
        } else if (x -> parent -> left == x)  {
            x -> parent -> left = y;
        } else if (x -> parent -> right == x) {
            x -> parent -> right = y;
        }

        if (y) y -> parent = x -> parent;
        return;
    }

    if (!x) return;
    if (root == x) {
        x -> parent = nullptr;
    }

    if (x -> parent == nullptr) {
        root = y;
    } else if (x -> parent -> left == x)  {
        x -> parent -> left = y;
    } else if (x -> parent -> right == x) {
        x -> parent -> right = y;
    }

    if (y) y -> parent = x -> parent;
}

Node* treeMinimum(Node* z) {
    Node* res = nullptr;
    while (z) {
        res = z;
        z = z -> left;
    }
    return res;
}

void PRBT::deleteNode(Node *z) {
    if (!z) return;
    Node* nil = nullptr;
    Node* y = z;
    Node* x;
    bool original = y -> color;
    if (z -> left == nullptr) {
        x = z -> right;
        if (!x) {
            nil = new Node;
            nil->color = false;
            nil->parent = z->parent;
        }
        transplant(z, z -> right);
    } else if (z -> right == nullptr) {
        x = z -> left;
        if (!x) {
            nil = new Node;
            nil->color = false;
            nil->parent = z->parent;
        }
        transplant(z, z -> left);
    } else {
        Node* y = treeMinimum(z -> right);
        original = y -> color;
        x = y -> right;

        bool ff = false;
        if (y -> parent == z) {
            if (x)
                x -> parent = y;
            else {

                ff = true;
                nil = new Node;
                nil -> color = false;

            }

        }
        else {

            if (! (y -> right)) {
                nil = new Node;
                nil -> color = false;
                nil -> parent = y -> parent;
            }

            transplant(y, y -> right);
            y -> right = z -> right;
            y -> right -> parent = y;
        }
        y -> left = z -> left;
        y -> left -> parent = y;
        y -> color = z -> color;
        transplant(z, y);
        if (ff) {
            nil -> parent = y -> parent;
        }
    }

    if (original == 0) {


        if (nil) {
            fixDeletion(nil);
        } else if (x) {
            fixDeletion (x);
        }
    }
}

void PRBT::fixDeletion(Node *x, int ind) {

    while (x != root && x -> color == 0) {



        if (x == x -> parent -> left) {
            Node* w = x -> parent -> right;
            if (w && w -> color == 1) {
                w -> color = false;
                x -> parent -> color = true;
                leftRotate(x -> parent);
                w = x -> parent -> right;

            }
            if ((w && w -> left && w -> left -> color == 0 && w -> right && w -> right -> color == 0)
                || (w && !(w -> left) && !(w -> right))){
                w -> color = true;
                x = x -> parent;

            }
            else if ((w && w -> right -> color == 0) || (w && !(w -> right))) {


                if (w -> left)
                    w -> left -> color = false;
                w -> color = true;
                rightRotate(w);
                w = x -> parent -> right;

            }

            if (w) w -> color = x -> parent -> color;
            x -> parent -> color = false;
            if (w && w -> right) w -> right -> color = false;
            leftRotate(x -> parent);
            x = root;

        } else {
            Node* w = x -> parent -> left;
            if (w && w -> color == 1) {
                w -> color = false;
                x -> parent -> color = true;
                rightRotate(x -> parent);
                w = x -> parent -> left;

            }
            if ((w && w -> right && w -> right -> color == 0 && w -> left && w -> left -> color == 0)
                || (w && !(w -> right) && !(w -> left))
                || (w && !(w -> right) && w -> left && w -> left -> color == 0)
                || (w && !(w -> left) && w -> right && w -> right -> color == 0)){
                w -> color = true;
                x = x -> parent;

            }
            else if ((w && w -> left -> color == 0) || (w && !(w -> left))) {


                if (w -> right)
                    w -> right -> color = false;
                w -> color = true;
                leftRotate(w);
                w = x -> parent -> left;

            }

            if (w) w -> color = x -> parent -> color;
            x -> parent -> color = false;
            if (w && w -> left) w -> left -> color = false;
            rightRotate(x -> parent);
            x = root;

        }
    }
    x -> color = false;
}


// PARTIAL PERSISTENCE FUNCTIONS, BEING TESTED

/*
void PRBT::pDelete(Node *i) {
    Node* nr = new Node;
    vers.roots.push_back(nr);
    if (vers.roots.size() > 1) {
        nr = vers.roots[vers.roots.size() - 2];
    } else {
        nr = nullptr;
    }
    Node* cur = nr;
    while (cur) {
        if (i -> key == cur -> key) {
            deleteNode(cur);
        }
        else if (i -> key < cur -> key) {
            Node* nl = new Node;
            nl = cur -> left;
            if (nl)
                nl -> parent = cur;
            cur -> left = nl;
            cur = cur -> left;
        } else {
            Node* nl = new Node;
            nl = cur -> right;

            if (nl)
                nl -> parent = cur;
            cur -> right = nl;
            cur = cur -> right;
        }
    }
}

 */

void PRBT::pInsert(Node *i) {
    auto nr = new Node;

    if (!vers.roots.empty()) {
        *nr = *vers.roots[vers.roots.size() - 1];
    } else {
        nr = nullptr;
    }

    vers.roots.push_back(nr);

    Node* prev = nullptr;
    Node* cur = nr;
    while (cur) {
        prev = cur;
        if (i -> key < cur -> key) {
            auto nl = new Node;
            if (cur -> left)
                *nl = *cur -> left;
            else
                nl = nullptr;

            if (nl)
                nl -> parent = cur;
            cur -> left = nl;

            cur = cur -> left;
        } else {
            auto nl = new Node;

            if (cur -> right)
                *nl = *cur -> right;
            else
                nl = nullptr;

            if (nl)
                nl -> parent = cur;
            cur -> right = nl;

            cur = cur -> right;
        }
    }

    i -> parent = prev;
    if (!prev) {

        vers.roots[vers.roots.size() - 1] = i;
    } else if (i -> key < prev -> key) {
        prev -> left = i;
    } else {
        prev -> right = i;
    }


    insertFixup(i, vers.roots.size() - 1);
}


