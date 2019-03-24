//
// Created by artyom on 04.03.19.
//

#include "OBT.h"

#include <iostream>
using std::cin;

#define eps 0.0000001
#define inf 100000000

double mabs(double a) {
    double res = a;
    if (res < 0) res *= -1;
    return res;
}

void OBT::accept() {

    cin >>  sz;
    qv.resize(sz + 1);
    pv.resize(sz + 1);
    keys.resize(sz + 1);

    for (int i = 0; i <= sz; i++) {
        keys[i] = i;
    }

    double q, p;
    double sum = 0;
    for (int i = 0; i <= sz; i++) {

        if (!i) {
            cin >> q;
            sum += q;
            qv[0] = q;
            continue;
        }

        cin >> q >> p;
        sum += q;
        sum += p;
        qv[i] = q;
        pv[i] = p;
    }

    std::cout << mabs(1 - sum);

    calc();
}

void OBT::calc() {

    e.clear();
    e.resize(sz + 2);
    for (int i = 0; i <= sz + 1; i++) {
        vector <double> tmp;
        tmp.resize(sz + 1);
        e[i] = tmp;
    }

    w.clear();
    w.resize(sz + 2);
    for (int i = 0; i <= sz + 1; i++) {
        vector <double > tmp;
        tmp.resize(sz + 1);
        w[i] = tmp;
    }

    roots.clear();
    roots.resize(sz + 1);
    for (int i = 0; i <= sz; i++) {
        vector <int> tmp;
        tmp.resize(sz + 1);
        roots[i] = tmp;
    }

    for (int i = 1; i <= sz + 1;i++) {
        e[i][i - 1] = qv[i - 1];
        w[i][i - 1] = qv[i - 1];
    }

    for (int l = 1; l <= sz; l++) {
        for (int i = 1; i <= sz - l + 1; i++) {
            int j = i + l - 1;
            e[i][j] = inf;

            w[i][j] = w[i][j - 1] + pv[j] + qv[j];
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j] + eps) {

                    e[i][j] = t;
                    roots[i][j] = r;
                }
            }
        }
    }
    root = construct(1, sz);
}

Node* OBT::construct(int i, int j) {
    if (i > j) {
        return nullptr;
    }
    if (i == j) {
        auto n = new Node;
        n -> parent = nullptr;
        n -> left = n -> right = nullptr;
        n -> key = keys[i];
        return n;
    }
    auto n = new Node;
    n -> parent = nullptr;
    n -> key = keys[roots[i][j]];
    n -> left = construct(i, roots[i][j] - 1);

    if (n -> left)
        n -> left -> parent = n;
    n -> right = construct(roots[i][j] + 1, j);
    if (n -> right)
        n -> right -> parent = n;

    return n;
}
