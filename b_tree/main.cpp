#include <iostream>
#include <string>
#include <vector>
#include "B_tree.h"
using std::cout;

#include <algorithm>


int main() {
    /*Book b(1);
    B_tree<Book> t(2);
    t.insert(b);
    auto p = t.search(b);*/

    B_tree<Book> t(2);

    for (int i = 0; i < 6; i++) {
        Book b(i);
        t.insert(b);
    }

    t.stackWrite();

    return 0;
}


