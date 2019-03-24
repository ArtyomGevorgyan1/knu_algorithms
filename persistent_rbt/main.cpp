#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;

struct Book {

public:
    Book() {
        hv = -1;
    }

    Book(const string &auth)
    {
        author = auth;
        hv = selfHash();
    }

    int selfHash() {
        int ret = 0;
        int pow = 1;
        for (int i = 0; i < author.size(); i++) {
            ret += author[i] * pow;
            pow *= 10;
        }
        return ret;
    }
private:
    int hv;
    string author;
};



const string arr[] = {
        "first",
        "second",
        "mouse",
        "Andrew",
        "Stats",
        "Stas",
        "seven",
        "eight",
        "hundred",
        "Gleb'sAdvice"
};

#include "PRBT.h"
int main() {
    PRBT t;


    Node* f;
    vector <Node*> vec;
    for (int i = 1; i < 10; i++) {
        f = t.getGoodNode(i);
        vec.push_back(f);
    }

    for (auto i : vec)

        t.pInsert(i);

    for (auto i: vec) {

        t.pDelete(i);
    }

    t.pInsert(t.getGoodNode(5));

    t.show(3);

    /*
    vector <Book*> vec;
    for (int i = 0; i < 10; i++) {
        Book* b = new Book(arr[i]);
        vec.push_back(b);
    }

    for (auto i : vec) {
        Node* j = t.getGoodNode(i->selfHash());
        t.pInsert(j);
    }
    */


    return 0;
}
