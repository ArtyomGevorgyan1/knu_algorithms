//
// Created by artyom on 04.03.19.
//

#ifndef OPT_BIN_TREE_OBT_H
#define OPT_BIN_TREE_OBT_H

#include <vector>
using std::vector;

struct Node {
    int key;
    Node* left, *right, *parent;
};

class OBT {
public:
    void accept();
    void calc();
    Node* construct(int i, int j);
private:
    int sz;
    vector <vector <double >> e;
    vector <vector <double >> w;
    vector <vector <int>> roots;
    vector <int> keys;

    vector <double> pv;
    vector <double> qv;
    Node* root;
};


#endif //OPT_BIN_TREE_OBT_H
