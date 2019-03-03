//
// Created by artyom on 25.02.19.
//

#include "STree.h"

#include <fstream>

ST::ST() {
    root = nullptr;
}

ST::~ST() {
    ;
}

void ST::show() {
    stackWrite();
    system("./show_png.sh");
}

void ST::stackWrite() {
    std::ofstream dotFile;
    dotFile.open ("./gr.dot");
    dotFile << "digraph BST {\n";
    //dotFile << "\t" << "a" << " [fillcolor=red style=filled];";

    std::stack <Node*> st;

    Node* cur = root;
    int cnt = 0;

    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur -> left;
        }
        cur = st.top();
        st.pop();
        if (cur -> left) {
            dotFile << "\t" << cur -> key << " -> " << cur -> left -> key << ";\n";
        }else {
            dotFile << "\t" << "null" << cnt << " [shape=point]" << ";\n";
            dotFile << "\t" << cur -> key << " -> " << "null" << cnt << ";\n";
            cnt++;
        }
        if (cur -> right) {
            dotFile << "\t" << cur -> key << " -> " << cur -> right -> key << ";\n";
        } else {
            dotFile << "\t" << "null" << cnt << " [shape=point]" << ";\n";
            dotFile << "\t" << cur -> key << " -> " << "null" << cnt << ";\n";
            cnt++;
        }
        cur = cur -> right;
    }

    dotFile << "}\n";
    dotFile.close();
}


void ST::insert(Node *i) {
    Node* cur = root;
    Node* prev = nullptr;
    while (cur) {
        prev = cur;
        if (i -> key < cur -> key) {
            cur = cur -> left;
        } else {
            cur = cur -> right;
        }

    }

    i -> parent = prev;
    if (prev == nullptr) {
        root = i;
    }
    else if (i -> key < prev -> key) {
        prev -> left = i;
    } else {
        prev -> right = i;
    }

    splay(i);
}


void ST::rRotate(Node *y) {
    Node* x = y -> left;
    y -> left = x -> right;
    if (x -> right) {
        x -> right -> parent = y;
    }
    x -> parent = y -> parent;
    if (y -> parent) {
        if (y == y -> parent -> left) {
            y -> parent -> left = x;
        } else {
            y -> parent -> right = x;
        }
    } else {
        root = x;
    }
    x -> right = y;
    y -> parent = x;
}

void ST::lRotate(Node *x) {
    Node* y = x -> right;
    x -> right = y -> left;
    if (y -> left) {
        x -> right = y -> left;
        y -> left -> parent = x;
    }
    y -> parent = x -> parent;
    if (x -> parent) {
        if (x == x -> parent -> left) {
            x -> parent -> left = y;
        } else {
            x -> parent -> right = y;
        }
    } else {
        root = y;
    }
    y -> left = x;
    x -> parent = y;
}

void ST::splay(Node *x) {

    while (x -> parent) {
        if (x -> parent && !(x -> parent -> parent)) {
            if (x == x -> parent -> left) {
                rRotate(x -> parent);
            } else {
                lRotate(x -> parent);
            }
        }
        else if (x -> parent && x -> parent -> parent && x == x -> parent -> left && x -> parent == x -> parent -> parent -> left) {
            rRotate(x -> parent -> parent);
            rRotate(x -> parent);
        }
        else if (x -> parent && x -> parent -> parent && x == x -> parent -> right && x -> parent == x -> parent -> parent -> right) {
            lRotate(x -> parent -> parent);
            lRotate(x -> parent);
        }
        else if (x -> parent && x -> parent -> parent && x == x -> parent -> left && x -> parent == x -> parent -> parent -> right) {
            rRotate(x -> parent);
            lRotate(x -> parent);
        }
        else if (x -> parent && x -> parent -> parent && x == x -> parent -> right && x -> parent == x -> parent -> parent -> left) {
            lRotate(x -> parent);
            rRotate(x -> parent);
        }
    }
}

Node *ST::getGoodNode(int k) {
    auto n = new Node;
    n -> key = k;
    n -> left = n -> right = n -> parent = nullptr;
    return n;
}

Node* ST::search(int k) {
    Node* cur = root;
    Node* prev = nullptr;
    while (cur) {
        prev = cur;
        if (cur -> key == k) {
            splay(cur);
            return cur;
        }
        else if (k < cur -> key) {
            cur = cur -> left;
        } else {
            cur = cur -> right;
        }
    }
    if (prev) {
        splay(prev);
    }
    return nullptr;
}

Node *ST::minElem(Node *x) {
    if (!x)
        return nullptr;

    Node* cur = x;
    while (cur -> left) {
        cur = cur -> left;
    }
    return cur;
}

Node *ST::maxElem(Node *x) {
    if (!x)
        return nullptr;

    Node* cur = x;
    while (cur -> right) {
        cur = cur -> right;
    }
    return cur;
}

Node* ST::join(Node *l, Node *r) {
    Node* nr = maxElem(l);
    _search(nr -> key, l);
    nr -> right = r;
    r -> parent = nr;
    return nr;
}

Node *ST::_search(int k, Node *r) {
    Node* cur = r;
    Node* prev = nullptr;
    while (cur) {
        prev = cur;
        if (cur -> key == k) {
            splay(cur);
            return cur;
        }
        else if (k < cur -> key) {
            cur = cur -> left;
        } else {
            cur = cur -> right;
        }
    }
    if (prev) {
        splay(prev);
    }
    return nullptr;
}

std::pair<Node *, Node *> ST::split(Node *t, int key) {
    _search(key, t);
    if (t -> key < key) {
        Node* r = t -> right;
        r -> parent = nullptr;
        t -> right = nullptr;
        return std::make_pair(t, r);
    } else {
        Node* l = t -> left;
        l -> parent = nullptr;
        t -> left = nullptr;
        return std::make_pair(l,t);
    }
}

void ST::remove(int key) {
    Node* n = search(key);
    if (n) {
        Node* y = n -> parent;
        if (y) {
            Node* nr = join(n -> left, n -> right);
            nr -> parent = y;
            if (n == n -> parent -> left) {
                y -> left = nr;
            } else {
                y -> right = nr;
            }
        } else {

            Node* nr = join(n -> left, n -> right);
            nr -> parent = nullptr;
            root = nr;
        }
    }
}

